.PHONY: all clean rstil

all: tests

clean:
	rm -rf bin/* gen/*

# Bootstrap: build rstil from Rust (required to run make.til)
RSTIL_SRCS := src/rstil.rs $(wildcard src/rs/*.rs)

bin/rstil: $(RSTIL_SRCS)
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

rstil: bin/rstil

# Prevent .rs files and Makefile from matching the % pattern.
# The % pattern below delegates unknown targets to make.til, but:
# - .rs files would create circular deps (bin/rstil depends on them)
# - Makefile gets checked by Make's automatic remaking feature
%.rs:
Makefile:
	@:

# Everything else delegates to make.til
%: bin/rstil
	./make.til $@
