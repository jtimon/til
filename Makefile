.PHONY: all clean test

all: bin/ctil

SRCS := $(wildcard src/*.c) $(wildcard src/c/*.c)
HDRS := $(wildcard src/c/*.h)

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -g -Isrc $(SRCS) -o bin/ctil

test: bin/ctil
	@bash tests.sh

clean:
	rm -rf bin/*
