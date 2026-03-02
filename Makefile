.PHONY: all clean

all: bin/ctil

SRCS := $(wildcard src/*.c) $(wildcard src/c/*.c)
HDRS := $(wildcard src/c/*.h)

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -g -std=c11 -Isrc $(SRCS) -o bin/ctil

clean:
	rm -rf bin/*
