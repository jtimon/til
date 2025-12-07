.PHONY: all tests repl til clean
all: rstil

rstil: src/rstil.rs
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

tests: rstil
	./bin/rstil src/tests.til
	# TODO: should be in tests.til but there's a non-deterministic bug when running from there
	./bin/rstil src/tests_codegen.til

# TODO run src/til.til with til.til
# TODO run src/tests.til with til.til
til: rstil tests
	./bin/rstil interpret src/til.til src/test/self/lexer/premode.til
	# ./bin/rstil interpret src/til.til help
	# ./bin/rstil interpret src/til.til src/test/strings.til
	# ./bin/rstil interpret src/til.til src/core/lexer.til

# REPL = Read-Eval-Print-Loop
repl: rstil
	rlwrap ./bin/rstil src/core/repl.til

clean:
	rm -rf bin/*
