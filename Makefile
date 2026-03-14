.PHONY: all clean test ctil_core

all: bin/ctil bin/c/til

SRCS := $(wildcard src/*.c) $(filter-out src/c/lexer.c, $(wildcard src/c/*.c)) bootstrap/lexer.c
HDRS := $(filter-out src/c/lexer.h, $(wildcard src/c/*.h)) bootstrap/lexer.h
CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)

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

bin/ctil: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -Werror -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil
	@$(MAKE) ctil_core
	cc -Wall -Wextra -Werror -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil

TIL_SRCS := $(filter-out src/ctil.c, $(SRCS))
bin/c/til: bin/ctil $(CORE) $(SELF) src/til.til
	@bin/ctil translate src/til.til
	@cc -Wall -Wextra -Werror -g -Isrc -Isrc/c $(TIL_SRCS) gen/c/til.c -Wl,--allow-multiple-definition -rdynamic -ldl $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/c/til

bin/c/test_runner: bin/ctil $(CORE) src/test_runner.til
	@bin/ctil build src/test_runner.til

bin/c/plot: bin/ctil $(CORE) src/examples/plot.til
	@bin/ctil build src/examples/plot.til

bin/c/tests: bin/ctil $(CORE) src/tests.til
	@bin/ctil build src/tests.til

gen/til/til.c: bin/c/til $(CORE) $(SELF) src/til.til
	@bin/c/til translate src/til.til

test: bin/ctil bin/c/til bin/c/test_runner bin/c/plot bin/c/tests gen/til/til.c
	@bin/c/tests $(if $(J),-j$(J))

ctil_core:
	@bin/ctil translate src/self/lexer.til
	@cp gen/c/lexer.c bootstrap/lexer.c
	@cp gen/c/lexer.h bootstrap/lexer.h
	@bin/ctil translate src/self/ast.til
	@cp gen/c/ast.c bootstrap/ast.c
	@cp gen/c/ast.h bootstrap/ast.h
	#@bin/ctil translate src/self/parser.til
	#@cp gen/c/parser.c bootstrap/parser.c
	#@cp gen/c/parser.h bootstrap/parser.h

bootstrap/til.c: bin/ctil $(CORE) $(SELF) src/til.til
	@bin/ctil translate src/til.til
	@cp gen/c/til.c bootstrap/til.c

bin/ctil_asan: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -fsanitize=address -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil_asan

bin/ctil_dbg: $(SRCS) $(HDRS) $(RAYLIB_LIB) lib/libffi/.built
	@mkdir -p bin
	cc -Wall -Wextra -g -O0 -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl $(LIBFFI_FLAGS) $(RAYLIB_FLAGS) -o bin/ctil_dbg

clean:
	rm -rf bin/*
	$(MAKE) -C lib/raylib/src clean
	cd $(LIBFFI_DIR) && $(MAKE) clean && rm -f .built
