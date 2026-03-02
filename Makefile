.PHONY: all clean

all: bin/ctil

SRCS := $(wildcard src/*.c)

bin/ctil: $(SRCS)
	@mkdir -p bin
	cc -Wall -Wextra -g -std=c11 $(SRCS) -o bin/ctil

clean:
	rm -rf bin/*
