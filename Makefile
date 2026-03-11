.PHONY: all clean test ctil_core

all: bin/ctil bin/c/til

SRCS := $(wildcard src/*.c) $(filter-out src/c/ext.c src/c/lexer.c, $(wildcard src/c/*.c)) src/bootstrap/lexer.c
HDRS := $(filter-out src/c/lexer.h, $(wildcard src/c/*.h)) src/bootstrap/lexer.h
CORE := $(wildcard src/core/*.til)
SELF := $(wildcard src/self/*.til)

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -Werror -Wno-unused-but-set-variable -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/ctil
	@$(MAKE) ctil_core
	cc -Wall -Wextra -Werror -Wno-unused-but-set-variable -g -Isrc -Isrc/c $(SRCS) -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/ctil

TIL_SRCS := $(filter-out src/ctil.c, $(SRCS))
bin/c/til: bin/ctil $(CORE) $(SELF) src/til.til
	@bin/ctil translate src/til.til
	@cc -Wall -Wextra -Werror -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-parameter -Wno-incompatible-pointer-types -Wno-pointer-sign -Wno-return-type -g -Isrc -Isrc/c $(TIL_SRCS) gen/c/til.c -Wl,--allow-multiple-definition -rdynamic -ldl -lffi -o bin/c/til

bin/c/test_runner: bin/ctil $(CORE) src/test_runner.til
	@bin/ctil build src/test_runner.til

bin/c/plot: bin/ctil $(CORE) src/examples/plot.til
	@bin/ctil build src/examples/plot.til

test: bin/ctil bin/c/til bin/c/test_runner bin/c/plot
	@bin/ctil interpret src/tests.til $(if $(J),-j$(J))

ctil_core: bin/ctil
	@bin/ctil translate src/self/lexer.til
	@cp gen/c/lexer.c src/bootstrap/lexer.c
	@cp gen/c/lexer.h src/bootstrap/lexer.h
	@bin/ctil translate src/self/parser.til
	@cp gen/c/parser.c src/bootstrap/parser.c
	@cp gen/c/parser.h src/bootstrap/parser.h

src/bootstrap/til.c: bin/ctil $(CORE) $(SELF) src/til.til
	@bin/ctil translate src/til.til
	@cp gen/c/til.c src/bootstrap/til.c

clean:
	rm -rf bin/*
