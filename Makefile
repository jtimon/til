.PHONY: all repl rscil cil

all: rscil cil
rscil:
	cargo run src/tests.cil
# TODO run src/cil.cil with cil.cil
# TODO run src/tests.cil with cil.cil
cil:
	cargo run interpret src/cil.cil src/test/example_self_hosted.cil
	# cargo run interpret src/cil.cil src/test/strings.cil
	# cargo run interpret src/cil.cil src/core/lexer.cil
repl:
	rlwrap cargo run src/core/repl.cil
