
.PHONY: all rscil cilcil test

all: rscil cilcil test
rscil:
	cargo build
cilcil: rscil
	cargo run src/cil.cil
test: rscil
	cargo run examples/hello.cil
	cargo run examples/hello_cli.cil
	cargo run examples/comparisons.cil
	cargo run examples/arithmetics.cil
	cargo run examples/branchless.cil
	cargo run examples/fib.cil
	cargo run examples/demo.cil
