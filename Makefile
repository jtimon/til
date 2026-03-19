.PHONY: all clean test test_headless til_core revert_boot rescue bisect

all: bin/til_bootstrap

SRCS := $(wildcard src/c/*.c) bootstrap/modes.c
HDRS := $(wildcard src/c/*.h) bootstrap/modes.h
CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
CC_FLAGS := -Wall -Wextra -Werror -g -Isrc -Isrc/c -Ibootstrap
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

# --- til (self-hosted compiler — two-pass gcc from bootstrap) ---
# Pass 1: gcc from committed bootstrap → compiler
# til_core: compiler regenerates bootstrap/ from .til sources
# Pass 2: gcc from regenerated bootstrap → final compiler
# bootstrap/modes.c in SRCS: modes.til is the facade (imports ast.til
# etc.), mode lib (no scavenging), so modes.c has all function bodies.

bin/til_bootstrap: $(SRCS) $(HDRS) $(CORE) $(SELF) bootstrap/til.c src/til.til $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc $(CC_FLAGS) $(SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap
	@$(MAKE) til_core
	cc $(CC_FLAGS) $(SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap

# --- programs built by til ---

bin/til/test_runner: bin/til_bootstrap $(CORE) $(SELF) src/test_runner.til
	@mkdir -p bin/til
	@bin/til_bootstrap build src/test_runner.til

bin/til/plot: bin/til_bootstrap $(CORE) $(SELF) src/examples/plot.til
	@mkdir -p bin/til
	@bin/til_bootstrap build src/examples/plot.til

bin/til/tests: bin/til_bootstrap $(CORE) $(SELF) src/tests.til
	@mkdir -p bin/til
	@bin/til_bootstrap build src/tests.til

# --- test suite ---

test: bin/til_bootstrap bin/til/test_runner bin/til/plot bin/til/tests
	@bin/til/tests $(if $(J),-j$(J))

test_headless: bin/til_bootstrap bin/til/test_runner bin/til/plot bin/til/tests
	@xvfb-run --auto-servernum bin/til/tests $(if $(J),-j$(J))

# --- bootstrap regeneration ---

til_core:
	@$(or $(TIL),bin/til_bootstrap) translate src/self/modes.til
	@cp gen/til/modes*.c gen/til/modes*.h bootstrap/ 2>/dev/null || true
	@$(or $(TIL),bin/til_bootstrap) translate src/til.til
	@cp gen/til/til*.c gen/til/til*.h bootstrap/ 2>/dev/null || true


# --- rescue: build compiler entirely from last commit's sources ---

rescue: $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p tmp/rescue/bootstrap tmp/rescue/src/c
	@for f in $$(git ls-tree --name-only HEAD bootstrap/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/rescue/$$f" 2>/dev/null || true; \
	done
	@for f in $$(git ls-tree --name-only HEAD src/c/ 2>/dev/null); do \
		git show "HEAD:$$f" > "tmp/rescue/$$f" 2>/dev/null || true; \
	done
	cc -Wall -Wextra -Werror -g -Isrc -Isrc/c -Itmp/rescue/bootstrap tmp/rescue/src/c/*.c tmp/rescue/bootstrap/modes.c tmp/rescue/bootstrap/til.c -Wl,--allow-multiple-definition $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o tmp/rescue/til
	@echo "Rescue compiler: tmp/rescue/til"

# --- debug/asan targets ---

bin/til_bootstrap_asan: $(SRCS) $(HDRS) bootstrap/til.c $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -fsanitize=address $(CC_FLAGS) $(SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap_asan

bin/til_bootstrap_dbg: $(SRCS) $(HDRS) bootstrap/til.c $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -O0 $(CC_FLAGS) $(SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap_dbg

revert_boot:
	git checkout HEAD bootstrap/
	git clean -fd bootstrap/

# Usage: make bisect GOOD=<commit>
# Finds the first commit after GOOD where make clean && make test fails.
bisect:
	git bisect start HEAD $(GOOD)
	git bisect run sh -c 'make clean && make test'
	git bisect reset

clean:
	rm -rf bin/* gen/* tmp/rescue
	$(MAKE) -C lib/raylib/src clean
	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
