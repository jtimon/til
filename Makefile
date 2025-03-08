.PHONY: all repl

all:
	cargo run src/tests.cil
repl:
	cargo run src/repl.cil
