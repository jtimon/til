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

.PHONY: all update_c_libs clean test test_asan test_asan_full test_nogui test_repl_help test_two_pass build_win doc help install tmp two_pass

all: bin/til

CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
LIB_TIL := $(wildcard lib/*.til) $(wildcard vendor/bindings/*.til)
LD_FLAGS := -rdynamic -ldl

RAYLIB_LIB := vendor/raylib/src/libraylib.a
RAYLIB_FLAGS := -Lvendor/raylib/src -lraylib -lm -lpthread -lrt

TINYFD_LIB := vendor/tinyfiledialogs/libtinyfd.a
TINYFD_FLAGS := -Lvendor/tinyfiledialogs -ltinyfd

LIBFFI_DIR := vendor/libffi
LIBFFI_INCDIR = $(firstword $(wildcard $(LIBFFI_DIR)/*/include))
LIBFFI_LIBDIR = $(firstword $(wildcard $(LIBFFI_DIR)/*/.libs))
LIBFFI_FLAGS = -I$(LIBFFI_INCDIR) -L$(LIBFFI_LIBDIR) -lffi
LIBFFI_BINDGEN_INCDIR := $(LIBFFI_DIR)/x86_64-pc-linux-gnu/include

$(RAYLIB_LIB):
	$(MAKE) -C vendor/raylib/src PLATFORM=PLATFORM_DESKTOP \
	  CUSTOM_CFLAGS="-DSUPPORT_CLIPBOARD_IMAGE=0 -I$(CURDIR)/vendor/x11/include"

$(TINYFD_LIB):
	cc -Wall -Wextra -c -o vendor/tinyfiledialogs/tinyfiledialogs.o vendor/tinyfiledialogs/tinyfiledialogs.c
	ar rcs $@ vendor/tinyfiledialogs/tinyfiledialogs.o

vendor/libffi/.built:
	cd $(LIBFFI_DIR) && ./configure --disable-shared --enable-static --disable-docs --quiet
	$(MAKE) -C $(LIBFFI_DIR)
	touch $@

# Bindings are produced by `bin/til bindings <header> -o <output.til>`
# (src/self/binder.til wired through src/til.til). The binder takes one
# C header, preprocesses with `cc -E -CC -dD`, filters back to the input
# directory, and writes a `mode lib` til file. No library-specific
# knowledge baked in -- callers add their own `link("...")` directive
# next to the `import(...)` site (see src/til.til and src/modes/gui.til).
#
# Manual only: `make update_c_libs` regenerates the in-tree
# vendor/bindings/*.til files.  Normal `make` / `make test` consumes
# whatever is committed there.  This is intentional: the auto-generator
# can't infer til-level qualifiers (proc vs func for purity, own vs ref
# for pointer ownership) from C headers alone, so the committed
# vendor/bindings/*.til files are hand-curated -- they happen to start
# their life as generator output but are edited in-tree afterwards.
# Running update_c_libs blows away those edits; redo the audit (see
# doc/ffi.org) before committing.
#
# raylib needs two headers: raylib.h plus rcamera.h (which raylib.h does
# not include but ships the CameraMoveForward/Right/Up helpers we need).
# Each is generated to a transient tmp/ file and concatenated, stripping
# the second `mode lib` so the combined file has exactly one mode
# header. rcamera.h references Camera / Vector3 / Matrix without
# including raylib.h; cc -E only preprocesses (no type checking) so the
# binder emits those decls verbatim and they resolve against the
# raylib.h block once the two are joined.
update_c_libs: bin/til | tmp
	mkdir -p vendor/bindings
	bin/til bindings -o vendor/bindings/tinyfd.til vendor/tinyfiledialogs/tinyfiledialogs.h
	bin/til bindings -o vendor/bindings/libffi.til $(LIBFFI_BINDGEN_INCDIR)/ffi.h
	bin/til bindings -o tmp/raylib_main.til vendor/raylib/src/raylib.h
	bin/til bindings -o tmp/rcamera.til vendor/raylib/src/rcamera.h
	cp tmp/raylib_main.til vendor/bindings/raylib.til
	sed -e '/^mode lib$$/d' tmp/rcamera.til >> vendor/bindings/raylib.til

# --- Boot compiler (from last commit, always safe) ---

bin/til_boot: $(RAYLIB_LIB) $(TINYFD_LIB) vendor/libffi/.built
	mkdir -p bin tmp/boot/boot tmp/boot/src/c
	for f in $$(git ls-tree --name-only HEAD boot/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	for f in $$(git ls-tree --name-only HEAD src/c/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	cc -Wall -Wextra -Werror -g -Itmp/boot/src -Itmp/boot/src/c -Itmp/boot/boot tmp/boot/src/c/*.c tmp/boot/boot/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) $(TINYFD_FLAGS) -o bin/til_boot

# --- Self-hosted compiler (current code) + regenerate boot/ ---

bin/til: bin/til_boot $(CORE) $(SELF) $(LIB_TIL) src/til.til
	C_INCLUDE_PATH=$(LIBFFI_INCDIR) LIBRARY_PATH=$(LIBFFI_LIBDIR) bin/til_boot build -o bin/til src/til.til
	cp gen/til/til.c gen/til/til_forward.h boot/ 2>/dev/null || true

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
# (see doc/bots/merging_from_remote.org).
two_pass: bin/til
	C_INCLUDE_PATH=$(LIBFFI_INCDIR) LIBRARY_PATH=$(LIBFFI_LIBDIR) bin/til build -o bin/til src/til.til
	cp gen/til/til.c gen/til/til_forward.h boot/ 2>/dev/null || true

# --- ASAN build (for memory debugging) ---
#
# Delegates to `bin/til build --asan`, which threads the sanitizer flags
# through src/self/builder.til. Same recipe is reusable for any .til
# program ("bin/til build --asan -o foo foo.til") so we can asan-test
# compiled outputs, not just the compiler itself.
bin/til_asan: bin/til
	bin/til build --asan -o bin/til_asan src/til.til

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
	xvfb-run --auto-servernum bin/tests --asan $(if $(J),-j$(J))
	cp gen/til/constfold.c test/constfold.c

# Two-pass equivalent of `make test`. Runs pass 2 first so bin/til reflects
# the self-applied compiler before tests build dependents from it. Use this
# when committing a "Two-pass: " change (see doc/self.org and the Makefile
# header comment on the two_pass target).
test_two_pass:
	$(MAKE) two_pass
	$(MAKE) test

# test_asan: alias for `test` -- the default suite now passes --asan to
# every `til build` / `til run` / `til test` invocation, so compiled test
# and example binaries always run ASAN-instrumented. Compiler still uses
# the regular bin/til so its known leaks aren't reported; see
# test_asan_full for the bin/til_asan variant.
test_asan: test

# test_asan_full: do both -- run the suite via the ASAN-instrumented compiler
# (bin/til_asan) AND pass --asan through so compiled binaries are sanitized too.
# Maximally strict. Compiler leaks are suppressed via asan_safe_cmd (the
# compiler itself is known to leak), but use-after-free / heap-buffer-overflow
# from either side still fail the run.
test_asan_full: bin/til bin/til_asan bin/test_runner bin/plot bin/tests
	xvfb-run --auto-servernum bin/tests --til-bin bin/til_asan --asan $(if $(J),-j$(J))

test_nogui: bin/til bin/test_runner bin/plot bin/tests
	bin/tests --no-gui $(if $(J),-j$(J))

# --- Doc generator (regenerates doc/gen/ and UML docs) ---
#
# Run on demand, not from `make test` -- doc gen on src/til.til runs the
# full init+typer pipeline and adds ~1 minute of wall time. Includes
# examples/uml.til, which is expensive enough to keep out of `make test`.
# Commit the refreshed doc/gen/ tree and UML outputs alongside notable
# doc-affecting changes.
doc: bin/til
	rm -rf doc/gen
	bin/til doc src/til.til
	bin/til run examples/uml.til

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
# (mode cli) -- test/repl_help.til.
test_repl_help: bin/til tmp
	bin/til run test/repl_help.til

# --- Windows cross-compilation ---

# Mingw-cross builds of raylib + tinyfd. Linux native builds stay in
# vendor/raylib/src/libraylib.a / vendor/tinyfiledialogs/libtinyfd.a; the
# Windows variants land alongside with -win64 suffixes. raylib's
# Makefile builds .o files in its own src/ dir, so we copy the sources
# into tmp/raylib-win/ first to avoid clobbering Linux .o files.
RAYLIB_WIN_LIB := vendor/raylib/src/libraylib-win64.a
TINYFD_WIN_LIB := vendor/tinyfiledialogs/libtinyfd-win64.a

$(RAYLIB_WIN_LIB):
	rm -rf tmp/raylib-win
	mkdir -p tmp/raylib-win
	cp -r vendor/raylib/src/. tmp/raylib-win/
	$(MAKE) -C tmp/raylib-win clean
	$(MAKE) -C tmp/raylib-win \
	  PLATFORM=PLATFORM_DESKTOP PLATFORM_OS=WINDOWS \
	  CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar \
	  RAYLIB_LIB_NAME=raylib-win64 RAYLIB_RELEASE_PATH=.
	cp tmp/raylib-win/libraylib-win64.a $@

$(TINYFD_WIN_LIB):
	mkdir -p tmp
	x86_64-w64-mingw32-gcc -c -o tmp/tinyfiledialogs-win.o vendor/tinyfiledialogs/tinyfiledialogs.c
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
	echo "make update_c_libs  Regenerate FFI bindings from C headers (manual; see doc/ffi.org)"
	echo "make doc            Regenerate doc/gen/ and UML docs"
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
#	$(MAKE) -C vendor/raylib/src clean
#	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
#	rm -f vendor/tinyfiledialogs/tinyfiledialogs.o vendor/tinyfiledialogs/libtinyfd.a
