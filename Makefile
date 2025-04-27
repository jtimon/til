.PHONY: all tests repl cil

all: cil tests cilrs
cilrs: src/cilrs.rs
	rustc src/cilrs.rs -o cilrs
tests: cilrs
	./cilrs src/tests.cil
# TODO run src/cil.cil with cil.cil
# TODO run src/tests.cil with cil.cil
cil: cilrs tests
	./cilrs interpret src/cil.cil src/test/example_self_hosted.cil
	# ./cilrs interpret src/cil.cil help
	# ./cilrs interpret src/cil.cil src/test/strings.cil
	# ./cilrs interpret src/cil.cil src/core/lexer.cil
repl:
	rlwrap ./cilrs src/core/repl.cil
