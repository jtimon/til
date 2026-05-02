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

.PHONY: all clean test test_asan test_nogui help

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

bin/plot: bin/til $(CORE) $(SELF) src/examples/plot.til
	bin/til build src/examples/plot.til

bin/tests: bin/til $(CORE) $(SELF) src/tests.til
	bin/til build src/tests.til

# --- Test suite ---

test: bin/til bin/test_runner bin/plot bin/tests
	xvfb-run --auto-servernum bin/tests $(if $(J),-j$(J))
	cp gen/til/constfold.c src/test/constfold.c

test_asan: bin/til bin/til_asan bin/test_runner bin/plot bin/tests
	xvfb-run --auto-servernum bin/tests --til-bin bin/til_asan $(if $(J),-j$(J))

test_nogui: bin/til bin/test_runner bin/plot bin/tests
	bin/tests --no-gui $(if $(J),-j$(J))

# --- Utilities ---

help:
	echo "make          Build bin/til + regenerate boot/"
	echo "make test     Build + run tests"
	echo "make clean    Remove build artifacts"
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
