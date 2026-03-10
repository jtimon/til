.PHONY: all clean test lib

all: bin/ctil

SRCS := $(wildcard src/*.c) $(filter-out src/c/ext.c, $(wildcard src/c/*.c)) src/lib/core.c
HDRS := $(wildcard src/c/*.h) src/lib/core.h

bin/ctil: $(SRCS) $(HDRS)
	@mkdir -p bin
	cc -Wall -Wextra -g -Isrc -Isrc/c $(SRCS) -rdynamic -ldl -lffi -o bin/ctil

test: bin/ctil
	@bin/ctil interpret src/tests.til $(if $(J),-j$(J))

lib: bin/ctil
	@bin/ctil translate src/core/core.til
	@cp gen/c/core.c src/lib/core.c
	@cp gen/c/core.h src/lib/core.h

clean:
	rm -rf bin/*
