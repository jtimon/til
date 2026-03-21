.PHONY: all clean test test_headless til_core revert_boot

all: bin/til_current

CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
CC_FLAGS := -Wall -Wextra -Werror -g -Isrc -Isrc/c -Iboot
LD_FLAGS := -Wl,--allow-multiple-definition -rdynamic -ldl

RAYLIB_LIB := lib/raylib/src/libraylib.a
RAYLIB_FLAGS := -Llib/raylib/src -lraylib -lm -lpthread -lrt

LIBFFI_DIR := lib/libffi
LIBFFI_FLAGS = -I$(firstword $(wildcard $(LIBFFI_DIR)/*/include)) -L$(firstword $(wildcard $(LIBFFI_DIR)/*/.libs)) -lffi

$(RAYLIB_LIB):
	$(MAKE) -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP CUSTOM_CFLAGS="-DSUPPORT_CLIPBOARD_IMAGE=0 -I$(CURDIR)/lib/x11/include"

lib/libffi/.built:
	cd $(LIBFFI_DIR) && ./configure --disable-shared --enable-static --quiet
	$(MAKE) -C $(LIBFFI_DIR)
	@touch $@

# --- Boot compiler (always from last commit, never breaks) ---

bin/til_boot: $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin tmp/boot/boot tmp/boot/src/c
	@for f in $$(git ls-tree --name-only HEAD boot/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	@for f in $$(git ls-tree --name-only HEAD src/c/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/boot/$$f" 2>/dev/null || true; \
	done
	cc -Wall -Wextra -Werror -g -Itmp/boot/src -Itmp/boot/src/c -Itmp/boot/boot tmp/boot/src/c/*.c tmp/boot/boot/modes.c tmp/boot/boot/til.c -Wl,--allow-multiple-definition $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_boot

# --- Current compiler (built by til_boot from current sources) ---

bin/til_current: bin/til_boot $(CORE) $(SELF) src/til.til
	bin/til_boot build -o bin/til_current src/til.til

# --- Regenerate boot/ (run before committing .til changes) ---

til_core: bin/til_boot
	@bin/til_boot translate src/self/modes.til
	@cp gen/til/modes*.c gen/til/modes*.h boot/ 2>/dev/null || true
	@bin/til_boot translate src/til.til
	@cp gen/til/til*.c gen/til/til*.h boot/ 2>/dev/null || true

# --- Programs built by current compiler ---

bin/test_runner: bin/til_current $(CORE) $(SELF) src/test_runner.til
	@bin/til_current build src/test_runner.til

bin/plot: bin/til_current $(CORE) $(SELF) src/examples/plot.til
	@bin/til_current build src/examples/plot.til

bin/tests: bin/til_current $(CORE) $(SELF) src/tests.til
	@bin/til_current build src/tests.til

# --- Test suite ---

test: bin/til_current bin/test_runner bin/plot bin/tests
	@bin/tests $(if $(J),-j$(J))

test_headless: bin/til_current bin/test_runner bin/plot bin/tests
	@xvfb-run --auto-servernum bin/tests $(if $(J),-j$(J))

# --- Utilities ---

revert_boot:
	git checkout HEAD boot/
	git clean -fd boot/

clean:
	rm -rf bin/* gen/* tmp/boot
	$(MAKE) -C lib/raylib/src clean
	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
