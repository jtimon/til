.PHONY: all clean

all: tests

clean:
	rm -rf bin/* gen/*

# Bootstrap: build rstil from Rust (required to compile make.til)
RSTIL_SRCS := src/rstil.rs $(wildcard src/rs/*.rs)

bin/rstil: $(RSTIL_SRCS)
	@mkdir -p bin
	rustc -D warnings src/rstil.rs -o bin/rstil

# Bootstrap make.til (first build only)
# After this, go_build_yourself() in make.til handles .til dependency tracking
# Bug #141: rstil outputs to bin/rs/
bin/rs/make: bin/rstil
	./bin/rstil build make.til --force-rebuild

# Prevent .rs, .til files and Makefile from matching the % pattern.
# The % pattern below delegates unknown targets to compiled make.til, but:
# - .rs files would create circular deps (bin/rstil depends on them)
# - .til files should not be treated as make targets
# - Makefile gets checked by Make's automatic remaking feature
%.rs:
%.til:
Makefile:
	@:

# Everything else delegates to compiled make.til
# Use $(MAKECMDGOALS) to pass all args (e.g., "make diff src/file.til")
%: bin/rs/make
	./bin/rs/make $(MAKECMDGOALS)
