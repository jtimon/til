.PHONY: all tests repl cil clean
all: tests rscil

rscil: src/rscil.rs
	@mkdir -p bin
	rustc src/rscil.rs -o bin/rscil

tests: rscil
	./bin/rscil src/tests.cil

# TODO run src/cil.cil with cil.cil
# TODO run src/tests.cil with cil.cil
cil: rscil tests
	./bin/rscil interpret src/cil.cil src/test/self/lexer/premode.cil
	# ./bin/rscil interpret src/cil.cil help
	# ./bin/rscil interpret src/cil.cil src/test/strings.cil
	# ./bin/rscil interpret src/cil.cil src/core/lexer.cil

# REPL = Read-Eval-Print-Loop
repl: rscil
	rlwrap ./bin/rscil src/core/repl.cil

clean:
	rm -rf bin/*
