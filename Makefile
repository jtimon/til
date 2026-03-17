.PHONY: all clean test ctil_core revert_bootstrap self_diff rescue

all: bin/ctil bin/c/til

SRCS := $(wildcard src/*.c) $(wildcard src/c/*.c) bootstrap/ast.c
HDRS := $(wildcard src/c/*.h) bootstrap/ast.h
CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
CC_FLAGS := -Wall -Wextra -Werror -g -Isrc -Isrc/c
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

# --- ctil (C entry point) ---

TIL_SRCS := $(filter-out src/ctil.c, $(SRCS))

bin/ctil: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc $(CC_FLAGS) $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil
	@$(MAKE) ctil_core
	cc $(CC_FLAGS) $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil

# --- til (til entry point — the self-hosted compiler) ---

bin/c/til: bin/ctil $(CORE) $(SELF) src/til.til
	@bin/ctil translate src/til.til
	@cc $(CC_FLAGS) $(TIL_SRCS) gen/c/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/c/til

# --- programs built by ctil ---

bin/c/test_runner: bin/ctil $(CORE) src/test_runner.til
	@bin/ctil build src/test_runner.til

bin/c/plot: bin/ctil $(CORE) src/examples/plot.til
	@bin/ctil build src/examples/plot.til

bin/c/tests: bin/ctil $(CORE) src/tests.til
	@bin/ctil build src/tests.til

# --- test suite ---

test: bin/ctil bin/c/til bin/c/test_runner bin/c/plot bin/c/tests
	@bin/c/tests $(if $(J),-j$(J))

# --- bootstrap regeneration ---

ctil_core:
	@bin/ctil translate src/self/ast.til
	@cp gen/c/ast.c bootstrap/ast.c
	@cp gen/c/ast.h bootstrap/ast.h
	@cp gen/c/ast_*.c bootstrap/ 2>/dev/null || true
	@cp gen/c/ast_*.h bootstrap/ 2>/dev/null || true
	@bin/ctil translate src/self/parser.til
	@cp gen/c/parser.c bootstrap/parser.c
	@cp gen/c/parser.h bootstrap/parser.h
	@cp gen/c/parser_*.c bootstrap/ 2>/dev/null || true
	@cp gen/c/parser_*.h bootstrap/ 2>/dev/null || true

self_diff: bin/ctil
	@$(MAKE) ctil_core
	@bin/ctil run scripts/self_diff.til

# --- rescue: build compiler from previous commit's bootstrap ---
# Use when breaking changes leave current bootstrap incompatible.

rescue: $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p tmp/rescue
	@git show HEAD~1:bootstrap/ast.c > tmp/rescue/ast.c
	@git show HEAD~1:bootstrap/ast.h > tmp/rescue/ast.h
	@for f in $$(git show HEAD~1:bootstrap/ 2>/dev/null | grep -v '^tree' | grep '\.c$$\|\.h$$'); do \
		git show "HEAD~1:bootstrap/$$f" > "tmp/rescue/$$f" 2>/dev/null || true; \
	done
	cc $(CC_FLAGS) $(filter-out bootstrap/ast.c,$(TIL_SRCS)) tmp/rescue/ast.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o tmp/rescue/til
	@echo "Rescue compiler: tmp/rescue/til"

# --- debug/asan targets ---

bin/ctil_asan: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -fsanitize=address -Isrc -Isrc/c $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil_asan

bin/c/til_asan: bin/ctil $(CORE) $(SELF) src/til.til
	@bin/ctil translate src/til.til
	cc -Wall -Wextra -g -fsanitize=address -Isrc -Isrc/c $(TIL_SRCS) gen/c/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/c/til_asan

bin/ctil_dbg: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -O0 -Isrc -Isrc/c $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil_dbg

revert_bootstrap:
	git checkout HEAD -- bootstrap/

clean:
	rm -rf bin/* tmp/rescue
	$(MAKE) -C lib/raylib/src clean
	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
