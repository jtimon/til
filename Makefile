.PHONY: all tests repl clean benchmark regen test-cross til_til diff_til
all: rstil

clean:
	rm -rf bin/* gen/*

# REPL = Read-Eval-Print-Loop
repl: rstil
	rlwrap ./bin/rstil repl

# Rust sources for rstil
RSTIL_SRCS := src/rstil.rs $(wildcard src/rs/*.rs)

bin/rstil: $(RSTIL_SRCS)
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

rstil: bin/rstil

# TIL sources for self-hosted compiler
TIL_SRCS := src/til.til $(wildcard src/self/*.til) $(wildcard src/core/*.til) $(wildcard src/std/*.til) $(wildcard src/modes/*.til)

bin/rstil_til: bin/rstil $(TIL_SRCS)
	./make.til rstil_til

rstil_til: bin/rstil_til

# WARNING: til_til currently hangs (see make.til for details)
til_til: rstil_til
	./make.til til_til

# WARNING: diff_til depends on til_til which hangs
diff_til: til_til
	./make.til diff_til

tests: rstil_til
	./make.til tests

regen: rstil_til
	./make.til regen

benchmark: rstil_til
	./make.til benchmark

test-cross: rstil_til
	./make.til test-cross
