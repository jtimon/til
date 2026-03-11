.PHONY: all clean test ctil_core

all: bin/ctil bin/c/til

SRCS := $(wildcard src/*.c) $(filter-out src/c/ext.c src/c/lexer.c, $(wildcard src/c/*.c)) src/bootstrap/lexer.c
HDRS := $(filter-out src/c/lexer.h, $(wildcard src/c/*.h)) src/bootstrap/lexer.h
SRC := $(wildcard src/core/*.til) $(wildcard src/self/*.til)

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/ctil
	@$(MAKE) ctil_core
	cc -Wall -Wextra -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/ctil

TIL_SRCS := $(filter-out src/ctil.c, $(SRCS))
bin/c/til: bin/ctil $(SRC) src/til.til
	@bin/ctil translate src/til.til
	@cc -g -Isrc -Isrc/c $(TIL_SRCS) gen/c/til.c -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/c/til

test: bin/ctil bin/c/til
	@bin/ctil interpret src/tests.til $(if $(J),-j$(J))

ctil_core: bin/ctil
	@bin/ctil translate src/self/lexer.til
	@cp gen/c/lexer.c src/bootstrap/lexer.c
	@cp gen/c/lexer.h src/bootstrap/lexer.h
	@bin/ctil translate src/self/parser.til
	@cp gen/c/parser.c src/bootstrap/parser.c
	@cp gen/c/parser.h src/bootstrap/parser.h

src/bootstrap/til.c: bin/ctil $(SRC) src/til.til
	@bin/ctil translate src/til.til
	@cp gen/c/til.c src/bootstrap/til.c

clean:
	rm -rf bin/*
