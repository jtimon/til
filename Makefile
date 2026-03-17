.PHONY: all clean test ctil_core til_core revert_bootstrap self_diff rescue

all: bin/ctil bin/til_bootstrap

SRCS := $(wildcard src/*.c) $(wildcard src/c/*.c) bootstrap/ast.c
HDRS := $(wildcard src/c/*.h) bootstrap/ast.h
CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)
CC_FLAGS := -Wall -Wextra -Werror -g -Isrc -Isrc/c -Ibootstrap
LD_FLAGS := -Wl,--allow-multiple-definition -rdynamic -ldl

RAYLIB_LIB := lib/raylib/src/libraylib.a
RAYLIB_FLAGS := -Llib/raylib/src -lraylib -lm -lpthread -lrt

LIBFFI_DIR := lib/libffi
LIBFFI_FLAGS = -I$(firstword $(wildcard $(LIBFFI_DIR)/*/include)) -L$(firstword $(wildcard $(LIBFFI_DIR)/*/.libs)) -lffi

TIL_SRCS := $(filter-out src/ctil.c, $(SRCS))

$(RAYLIB_LIB):
	$(MAKE) -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP CUSTOM_CFLAGS="-DSUPPORT_CLIPBOARD_IMAGE=0 -I$(CURDIR)/lib/x11/include"

lib/libffi/.built:
	cd $(LIBFFI_DIR) && ./configure --disable-shared --enable-static --quiet
	$(MAKE) -C $(LIBFFI_DIR)
	@touch $@

# --- ctil (C entry point — kept temporarily) ---

bin/ctil: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc $(CC_FLAGS) $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil
	@$(MAKE) ctil_core
	cc $(CC_FLAGS) $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil

# --- til (self-hosted compiler — two-pass gcc from bootstrap) ---

bin/til_bootstrap: $(TIL_SRCS) $(HDRS) bootstrap/til.c $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc $(CC_FLAGS) $(TIL_SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap
	@$(MAKE) til_core
	cc $(CC_FLAGS) $(TIL_SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap

# --- programs built by til ---

bin/til/test_runner: bin/til_bootstrap $(CORE) src/test_runner.til
	@bin/til_bootstrap build src/test_runner.til

bin/til/plot: bin/til_bootstrap $(CORE) src/examples/plot.til
	@bin/til_bootstrap build src/examples/plot.til

bin/til/tests: bin/til_bootstrap $(CORE) src/tests.til
	@bin/til_bootstrap build src/tests.til

# --- test suite ---

test: bin/til_bootstrap bin/til/test_runner bin/til/plot bin/til/tests
	@bin/til/tests $(if $(J),-j$(J))

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
	@bin/ctil translate src/til.til
	@cp gen/c/til.c bootstrap/til.c
	@cp gen/c/til_*.c bootstrap/ 2>/dev/null || true
	@cp gen/c/til_*.h bootstrap/ 2>/dev/null || true

til_core:
	@bin/til_bootstrap translate src/self/ast.til
	@cp gen/til/ast.c bootstrap/ast.c
	@cp gen/til/ast.h bootstrap/ast.h
	@cp gen/til/ast_*.c bootstrap/ 2>/dev/null || true
	@cp gen/til/ast_*.h bootstrap/ 2>/dev/null || true
	@bin/til_bootstrap translate src/self/parser.til
	@cp gen/til/parser.c bootstrap/parser.c
	@cp gen/til/parser.h bootstrap/parser.h
	@cp gen/til/parser_*.c bootstrap/ 2>/dev/null || true
	@cp gen/til/parser_*.h bootstrap/ 2>/dev/null || true
	@bin/til_bootstrap translate src/til.til
	@cp gen/til/til.c bootstrap/til.c
	@cp gen/til/til_*.c bootstrap/ 2>/dev/null || true
	@cp gen/til/til_*.h bootstrap/ 2>/dev/null || true

self_diff: bin/til_bootstrap
	@$(MAKE) til_core
	@bin/til_bootstrap run scripts/self_diff.til

# --- rescue: build compiler from previous commit's bootstrap ---

rescue: $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p tmp/rescue
	@for f in $$(git ls-tree --name-only HEAD~1 bootstrap/ 2>/dev/null); do \
		git show "HEAD~1:$$f" > "tmp/rescue/$$(basename $$f)" 2>/dev/null || true; \
	done
	cc $(CC_FLAGS) $(filter-out bootstrap/%,$(TIL_SRCS)) tmp/rescue/*.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o tmp/rescue/til
	@echo "Rescue compiler: tmp/rescue/til"

# --- debug/asan targets ---

bin/ctil_asan: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -fsanitize=address $(CC_FLAGS) $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil_asan

bin/til_bootstrap_asan: $(TIL_SRCS) $(HDRS) bootstrap/til.c $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -fsanitize=address $(CC_FLAGS) $(TIL_SRCS) bootstrap/til.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/til_bootstrap_asan

bin/ctil_dbg: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -O0 -Isrc -Isrc/c -Ibootstrap $(SRCS) $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil_dbg

revert_bootstrap:
	git checkout HEAD -- bootstrap/

clean:
	rm -rf bin/* tmp/rescue
	$(MAKE) -C lib/raylib/src clean
	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
