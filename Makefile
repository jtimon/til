.PHONY: all clean

all: tests

clean:
	rm -rf bin/* gen/*

# Bootstrap: build rstil from Rust (required to compile make.til)
RSTIL_SRCS := src/rstil.rs $(wildcard src/rs/*.rs)

bin/rstil: $(RSTIL_SRCS)
	@mkdir -p bin
	rustc -D warnings src/rstil.rs -o bin/rstil

# Compiled make.til for faster builds
MAKE_TIL_DEPS := make.til $(wildcard src/std/*.til) $(wildcard src/core/*.til)

bin/make: bin/rstil $(MAKE_TIL_DEPS)
	./bin/rstil build make.til

# Prevent .rs, .til files and Makefile from matching the % pattern.
# The % pattern below delegates unknown targets to compiled make.til, but:
# - .rs files would create circular deps (bin/rstil depends on them)
# - .til files would create circular deps (bin/make depends on them)
# - Makefile gets checked by Make's automatic remaking feature
%.rs:
%.til:
Makefile:
	@:

# Everything else delegates to compiled make.til
%: bin/make
	./bin/make $@
