.PHONY: all tests repl cil

all: rscil cil tests
rscil: src/main.rs
	rustc src/main.rs -o rscil
tests: rscil
	./rscil src/tests.cil
# TODO run src/cil.cil with cil.cil
# TODO run src/tests.cil with cil.cil
cil: rscil tests
	./rscil interpret src/cil.cil src/test/example_self_hosted.cil
	# ./rscil interpret src/cil.cil src/test/strings.cil
	# ./rscil interpret src/cil.cil src/core/lexer.cil
repl:
	rlwrap ./rscil src/core/repl.cil
