# til Makefile
#
# make          Build bin/til (self-hosted compiler) + regenerate boot/
# make test     Build + run all tests
# make clean    Remove all build artifacts
# make help     Show this help
#
# bin/til_boot  Built from last commit via git. Always safe. Never fails.
# bin/til       Built by til_boot from current .til sources.
#               When changes break things, bin/til fails -- til_boot is fine.
# boot/         Generated C checked into repo. Regenerated every build
#               so the next commit's til_boot has current code.

.PHONY: all clean test test_headless revert_boot help

all: bin/til

CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
LD_FLAGS := -Wl,--allow-multiple-definition -rdynamic -ldl

RAYLIB_LIB := lib/raylib/src/libraylib.a
RAYLIB_FLAGS := -Llib/raylib/src -lraylib -lm -lpthread -lrt

LIBFFI_DIR := lib/libffi
LIBFFI_FLAGS = -I$(firstword $(wildcard $(LIBFFI_DIR)/*/include)) \
               -L$(firstword $(wildcard $(LIBFFI_DIR)/*/.libs)) -lffi

$(RAYLIB_LIB):
	$(MAKE) -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP \
	  CUSTOM_CFLAGS="-DSUPPORT_CLIPBOARD_IMAGE=0 -I$(CURDIR)/lib/x11/include"

lib/libffi/.built:
	cd $(LIBFFI_DIR) && ./configure --disable-shared --enable-static --quiet
	$(MAKE) -C $(LIBFFI_DIR)
	touch $@

# --- Boot compiler (from last commit, always safe) ---

bin/til_boot: $(RAYLIB_LIB) lib/libffi/.built
	mkdir -p bin tmp/boot/boot tmp/boot/src/c
	for f in $$(git ls-tree --name-only HEAD boot/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	for f in $$(git ls-tree --name-only HEAD src/c/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	cc -Wall -Wextra -Werror -g -Itmp/boot/src -Itmp/boot/src/c -Itmp/boot/boot tmp/boot/src/c/*.c tmp/boot/boot/modes.c tmp/boot/boot/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_boot

# --- Self-hosted compiler (current code) + regenerate boot/ ---

bin/til: bin/til_boot $(CORE) $(SELF) src/til.til
	bin/til_boot build -o bin/til src/til.til
	bin/til translate src/self/modes.til
	cp gen/til/modes*.c gen/til/modes*.h boot/ 2>/dev/null || true
	bin/til translate src/til.til
	cp gen/til/til*.c gen/til/til*.h boot/ 2>/dev/null || true

# --- ASAN build (for memory debugging) ---

bin/til_asan: bin/til $(CORE) $(SELF) src/til.til
	bin/til translate src/til.til
	cc -fsanitize=address -fno-omit-frame-pointer -g -Wno-all \
	  -Igen/til -Isrc -Isrc/c gen/til/til.c src/c/*.c \
	  $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) \
	  -fsanitize=address -o bin/til_asan

# --- Test programs ---

bin/test_runner: bin/til $(CORE) $(SELF) src/test_runner.til
	bin/til build src/test_runner.til

bin/plot: bin/til $(CORE) $(SELF) src/examples/plot.til
	bin/til build src/examples/plot.til

bin/tests: bin/til $(CORE) $(SELF) src/tests.til
	bin/til build src/tests.til

# --- Test suite ---

test: bin/til bin/test_runner bin/plot bin/tests
	bin/tests $(if $(J),-j$(J))

test_headless: bin/til bin/test_runner bin/plot bin/tests
	xvfb-run --auto-servernum bin/tests $(if $(J),-j$(J))

# --- Utilities ---

revert_boot:
	git checkout HEAD boot/
	git clean -fd boot/

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
	echo "Recovery: make revert_boot && make test"

clean:
	rm -rf bin/* gen/* tmp/boot
	$(MAKE) -C lib/raylib/src clean
	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
