.PHONY: all clean test til_core revert_boot self_diff rescue bisect

all: bin/til_bootstrap

SRCS := $(wildcard src/c/*.c) bootstrap/ast.c
HDRS := $(wildcard src/c/*.h) bootstrap/ast.h
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
# bootstrap/ast.c in SRCS ensures linking always succeeds: ast.til is
# mode lib (no scavenging), so ast.c always has all function bodies.

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

# --- bootstrap regeneration ---

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
	@bin/til_bootstrap translate src/self/modes.til
	@cp gen/til/modes.c bootstrap/modes.c
	@cp gen/til/modes.h bootstrap/modes.h
	@cp gen/til/modes_*.c bootstrap/ 2>/dev/null || true
	@cp gen/til/modes_*.h bootstrap/ 2>/dev/null || true
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
	cc $(CC_FLAGS) $(filter-out bootstrap/%,$(SRCS)) tmp/rescue/*.c $(LD_FLAGS) $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o tmp/rescue/til
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
