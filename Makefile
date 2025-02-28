
.PHONY: all rscil cilcil test

all: rscil cilcil test demo
rscil:
	cargo build
cilcil: rscil
	cargo run src/cil.cil
test: rscil cilcil
	cargo run examples/arithmetics.cil
	cargo run examples/boolean.cil
	cargo run examples/branchless.cil
	cargo run examples/comparisons.cil
	cargo run examples/execution.cil
	cargo run examples/fib.cil
	cargo run examples/hello.cil
	cargo run examples/hello_cli.cil
demo: rscil test
	cargo run examples/demo.cil
