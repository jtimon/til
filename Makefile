.PHONY: all tests repl cil

all: cil tests rscil
rscil: src/rscil.rs
	rustc src/rscil.rs -o rscil
tests: rscil
	./rscil src/tests.cil
# TODO run src/cil.cil with cil.cil
# TODO run src/tests.cil with cil.cil
cil: rscil tests
	./rscil interpret src/cil.cil src/test/example_self_hosted.cil
	# ./rscil interpret src/cil.cil help
	# ./rscil interpret src/cil.cil src/test/strings.cil
	# ./rscil interpret src/cil.cil src/core/lexer.cil
repl:
	rlwrap ./rscil src/core/repl.cil
