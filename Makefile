# til Makefile
#
# make          Build bin/til (self-hosted compiler) + regenerate boot/
# make test     Build + run all tests
# make clean    Remove all build artifacts
# make help     Show this help
#
# bin/til_boot  Built from last commit via git (boot/ + src/c/ from HEAD).
#               Completely isolated from uncommitted changes. Always safe.
# bin/til       Built by til_boot from ALL current sources (.til + src/c/).
#               Most .til and C changes take effect immediately. Emit-side
#               changes (e.g. new auto-gen methods) need a preparation
#               commit -- see doc/self.org.
# boot/         Generated C checked into repo. Regenerated every build
#               so the next commit's til_boot has current code.

.PHONY: all clean test test_asan test_nogui test_repl_help test_two_pass build_win doc help install tmp two_pass

all: bin/til

CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
LD_FLAGS := -rdynamic -ldl

RAYLIB_LIB := lib/raylib/src/libraylib.a
RAYLIB_FLAGS := -Llib/raylib/src -lraylib -lm -lpthread -lrt

TINYFD_LIB := lib/tinyfiledialogs/libtinyfd.a
TINYFD_FLAGS := -Llib/tinyfiledialogs -ltinyfd

LIBFFI_DIR := lib/libffi
LIBFFI_INCDIR = $(firstword $(wildcard $(LIBFFI_DIR)/*/include))
LIBFFI_LIBDIR = $(firstword $(wildcard $(LIBFFI_DIR)/*/.libs))
LIBFFI_FLAGS = -I$(LIBFFI_INCDIR) -L$(LIBFFI_LIBDIR) -lffi

$(RAYLIB_LIB):
	$(MAKE) -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP \
	  CUSTOM_CFLAGS="-DSUPPORT_CLIPBOARD_IMAGE=0 -I$(CURDIR)/lib/x11/include"

$(TINYFD_LIB):
	cc -Wall -Wextra -c -o lib/tinyfiledialogs/tinyfiledialogs.o lib/tinyfiledialogs/tinyfiledialogs.c
	ar rcs $@ lib/tinyfiledialogs/tinyfiledialogs.o

lib/libffi/.built:
	cd $(LIBFFI_DIR) && ./configure --disable-shared --enable-static --disable-docs --quiet
	$(MAKE) -C $(LIBFFI_DIR)
	touch $@

# --- Boot compiler (from last commit, always safe) ---

bin/til_boot: $(RAYLIB_LIB) $(TINYFD_LIB) lib/libffi/.built
	mkdir -p bin tmp/boot/boot tmp/boot/src/c
	for f in $$(git ls-tree --name-only HEAD boot/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	for f in $$(git ls-tree --name-only HEAD src/c/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	cc -Wall -Wextra -Werror -g -Itmp/boot/src -Itmp/boot/src/c -Itmp/boot/boot tmp/boot/src/c/*.c tmp/boot/boot/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) $(TINYFD_FLAGS) -o bin/til_boot

# --- Self-hosted compiler (current code) + regenerate boot/ ---

bin/til: bin/til_boot $(CORE) $(SELF) src/til.til
	C_INCLUDE_PATH=$(LIBFFI_INCDIR) LIBRARY_PATH=$(LIBFFI_LIBDIR) bin/til_boot build -o bin/til src/til.til
	cp gen/til/til.c gen/til/til.h gen/til/til_forward.h boot/ 2>/dev/null || true

# --- Two-pass build ---
#
# Pass 1 (the bin/til prerequisite) compiles current sources with til_boot
# from HEAD. Pass 2 reruns the build using the freshly-compiled bin/til so
# the resulting boot/til.c reflects the new compiler self-applied. Use this
# when a single commit must ship both an emit-side change and the boot
# artifacts that change would produce when applied to itself; without
# two_pass the same outcome takes two commits (preparation + use, see
# doc/self.org). Commits relying on this target MUST be prefixed
# "Two-pass: " so the local merger reproduces the same regen procedure
# (see bots/merging_from_remote.org).
two_pass: bin/til
	C_INCLUDE_PATH=$(LIBFFI_INCDIR) LIBRARY_PATH=$(LIBFFI_LIBDIR) bin/til build -o bin/til src/til.til
	cp gen/til/til.c gen/til/til.h gen/til/til_forward.h boot/ 2>/dev/null || true

# --- ASAN build (for memory debugging) ---

bin/til_asan: bin/til
	cc -fsanitize=address -fno-omit-frame-pointer -g -Wno-all \
	  -Iboot -Isrc -Isrc/c boot/til.c src/c/*.c \
	  $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) $(TINYFD_FLAGS) \
	  -fsanitize=address -o bin/til_asan

# --- Debug build (for gdb) ---

bin/til_debug: bin/til
	cc -g -O0 -Wno-all \
	  -Iboot -Isrc -Isrc/c boot/til.c src/c/*.c \
	  $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) $(TINYFD_FLAGS) \
	  -o bin/til_debug

# --- Test programs ---

bin/test_runner: bin/til $(CORE) $(SELF) src/test_runner.til
	bin/til build src/test_runner.til

bin/plot: bin/til $(CORE) $(SELF) examples/plot.til
	bin/til build examples/plot.til

bin/tests: bin/til $(CORE) $(SELF) src/tests.til
	bin/til build src/tests.til

# --- Test suite ---

test: bin/til bin/test_runner bin/plot bin/tests
	xvfb-run --auto-servernum bin/tests $(if $(J),-j$(J))
	cp gen/til/constfold.c src/test/constfold.c

# Two-pass equivalent of `make test`. Runs pass 2 first so bin/til reflects
# the self-applied compiler before tests build dependents from it. Use this
# when committing a "Two-pass: " change (see doc/self.org and the Makefile
# header comment on the two_pass target).
test_two_pass:
	$(MAKE) two_pass
	$(MAKE) test

test_asan: bin/til bin/til_asan bin/test_runner bin/plot bin/tests
	xvfb-run --auto-servernum bin/tests --til-bin bin/til_asan $(if $(J),-j$(J))

test_nogui: bin/til bin/test_runner bin/plot bin/tests
	bin/tests --no-gui $(if $(J),-j$(J))

# --- Doc generator (regenerates doc/gen/ from current sources) ---

# Run on demand, not from `make test` -- doc gen on src/til.til runs the
# full init+typer pipeline and adds ~1 minute of wall time. Commit the
# refreshed doc/gen/ tree alongside notable doc-affecting changes.
doc: bin/til
	rm -rf doc/gen
	bin/til doc src/til.til

install: bin/til
	bin/til install src/til.til
# Shared writable scratch dir for targets that need it (test_repl_help
# writes the REPL stdin/stdout fixtures there; til_boot copies snapshot
# sources into tmp/boot/).
tmp:
	mkdir -p tmp

# --- REPL help() smoke test ---
#
# Pipes a single help() call into bin/til, captures stdout, and verifies
# the expected core doc text appears. Run on demand because the REPL
# spawns bin/til + a til interpret subprocess per turn, which dominates
# `make test` wall time. The test driver itself is a TIL script
# (mode cli) -- src/test/repl_help.til.
test_repl_help: bin/til tmp
	bin/til run src/test/repl_help.til

# --- Windows cross-compilation ---

# Mingw-cross builds of raylib + tinyfd. Linux native builds stay in
# lib/raylib/src/libraylib.a / lib/tinyfiledialogs/libtinyfd.a; the
# Windows variants land alongside with -win64 suffixes. raylib's
# Makefile builds .o files in its own src/ dir, so we copy the sources
# into tmp/raylib-win/ first to avoid clobbering Linux .o files.
RAYLIB_WIN_LIB := lib/raylib/src/libraylib-win64.a
TINYFD_WIN_LIB := lib/tinyfiledialogs/libtinyfd-win64.a

$(RAYLIB_WIN_LIB):
	rm -rf tmp/raylib-win
	mkdir -p tmp/raylib-win
	cp -r lib/raylib/src/. tmp/raylib-win/
	$(MAKE) -C tmp/raylib-win clean
	$(MAKE) -C tmp/raylib-win \
	  PLATFORM=PLATFORM_DESKTOP PLATFORM_OS=WINDOWS \
	  CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar \
	  RAYLIB_LIB_NAME=raylib-win64 RAYLIB_RELEASE_PATH=.
	cp tmp/raylib-win/libraylib-win64.a $@

$(TINYFD_WIN_LIB):
	mkdir -p tmp
	x86_64-w64-mingw32-gcc -c -o tmp/tinyfiledialogs-win.o lib/tinyfiledialogs/tinyfiledialogs.c
	x86_64-w64-mingw32-ar rcs $@ tmp/tinyfiledialogs-win.o

# raylib.til is a "direct raylib FFI" demo with hardcoded Linux link()
# paths -- it deliberately doesn't use mode gui. Excluded from the
# cross-compile sweep; the other 24 examples cover the Windows build.
WIN_EXAMPLES_SRC := $(filter-out examples/raylib.til,$(wildcard examples/*.til))
WIN_EXAMPLES := $(patsubst examples/%.til,bin/%.exe,$(WIN_EXAMPLES_SRC))

build_win: $(RAYLIB_WIN_LIB) $(TINYFD_WIN_LIB) $(WIN_EXAMPLES)

bin/%.exe: examples/%.til bin/til $(RAYLIB_WIN_LIB) $(TINYFD_WIN_LIB)
	bin/til build --target=windows-x64 $<

# --- Utilities ---

help:
	echo "make                Build bin/til + regenerate boot/"
	echo "make test           Build + run tests"
	echo "make two_pass       Build, then rebuild with the fresh bin/til"
	echo "make test_two_pass  two_pass + run tests (use for 'Two-pass: ' commits)"
	echo "make doc            Regenerate doc/gen/ from current sources"
	echo "make install        Install til under PREFIX (default /usr/local)"
	echo "make clean          Remove build artifacts"
	echo ""
	echo "bin/til_boot  From last commit (git). Always works."
	echo "bin/til       From current sources. May break."
	echo "boot/         Generated C. Committed for til_boot."
	echo ""
	echo "Workflow: make test, then commit (including boot/)."
	echo "Recovery: git checkout HEAD boot/ && make test"

clean:
	rm -rf bin/* gen/*
	rm -rf tmp/boot
# REM uncoment when upgrading dependency libraries
#	$(MAKE) -C lib/raylib/src clean
#	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
#	rm -f lib/tinyfiledialogs/tinyfiledialogs.o lib/tinyfiledialogs/libtinyfd.a
