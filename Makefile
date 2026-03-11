.PHONY: all clean test ctil_core

all: bin/ctil

SRCS := $(wildcard src/*.c) $(filter-out src/c/ext.c src/c/lexer.c, $(wildcard src/c/*.c)) src/bootstrap/lexer.c
HDRS := $(filter-out src/c/lexer.h, $(wildcard src/c/*.h)) src/bootstrap/lexer.h
SRC := $(wildcard src/core/*.til) $(wildcard src/self/*.til)

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/ctil
	@$(MAKE) ctil_core
	cc -Wall -Wextra -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/ctil

test: bin/ctil
	@bin/ctil interpret src/tests.til $(if $(J),-j$(J))

ctil_core: bin/ctil
	@bin/ctil translate src/self/lexer.til
	@cp gen/c/lexer.c src/bootstrap/lexer.c
	@cp gen/c/lexer.h src/bootstrap/lexer.h

src/bootstrap/til.c: bin/ctil $(SRC) src/self/til.til
	@bin/ctil translate src/self/til.til
	@cp gen/c/til.c src/bootstrap/til.c

clean:
	rm -rf bin/*
