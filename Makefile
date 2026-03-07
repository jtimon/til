.PHONY: all clean test

all: bin/ctil

SRCS := $(wildcard src/*.c) $(wildcard src/c/*.c)
HDRS := $(wildcard src/c/*.h)

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -g -Isrc $(SRCS) -rdynamic -ldl -lffi -o bin/ctil

test: bin/ctil
	@bin/ctil interpret src/tests.til $(if $(J),-j$(J))

clean:
	rm -rf bin/*
