.PHONY: all clean

all: tests

clean:
	rm -rf bin/* gen/*

# Bootstrap: build rstil from Rust sources
RSTIL_SRCS := src/rstil.rs $(wildcard src/rs/*.rs)

bin/rstil: $(RSTIL_SRCS)
	@mkdir -p bin
	rustc -D warnings src/rstil.rs -o bin/rstil

# Prevent .rs, .til files and Makefile from matching the % pattern
%.rs:
%.til:
Makefile:
	@:

# Everything else delegates to make.til (which handles its own rebuilding)
%: bin/rstil
	./make.til $@
