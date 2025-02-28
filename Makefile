
.PHONY: all cilcil test demo

all: test
test:
	cargo run src/tests.cil
cilcil:
	cargo run src/cil.cil
demo:
	cargo run examples/demo.cil
