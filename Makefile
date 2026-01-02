.PHONY: all tests repl clean benchmark regen test-cross
all: rstil

clean:
	rm -rf bin/* gen/*

# REPL = Read-Eval-Print-Loop
repl: rstil
	rlwrap ./bin/rstil repl

# Rust sources for rstil
RSTIL_SRCS := src/rstil.rs $(wildcard src/rs/*.rs)

bin/rstil: $(RSTIL_SRCS)
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

rstil: bin/rstil

# TIL sources for self-hosted compiler
TIL_SRCS := src/til.til $(wildcard src/self/*.til) $(wildcard src/core/*.til) $(wildcard src/std/*.til) $(wildcard src/modes/*.til)

bin/til: bin/rstil $(TIL_SRCS)
	./bin/rstil build src/til.til
	cp gen/c/til.c bootstrap/til.c

rstil_til: bin/til

tests: rstil_til
	./bin/rstil interpret src/tests.til
	cp gen/c/test/constfold.c src/test/constfold.c
	@echo "Remember to add generated files to commit: bootstrap/til.c, src/test/constfold.c"

regen: rstil rstil_til
	./bin/rstil interpret src/tests.til regen
	@echo "Regenerated all test outputs"

benchmark: tests
	@cp gen/benchmark.org doc/benchmark.org
	@echo "Benchmark saved to doc/benchmark.org, can be committed"

test-cross: rstil rstil_til
	@echo "=== Cross-compilation tests ==="
	@echo "linux-arm64..."
	./bin/rstil build src/examples/hello_script.til --target=linux-arm64
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./src/examples/bin/hello_script
	@echo "linux-riscv64..."
	./bin/rstil build src/examples/hello_script.til --target=linux-riscv64
	qemu-riscv64 -L /usr/riscv64-linux-gnu ./src/examples/bin/hello_script
	@echo "windows-x64..."
	./bin/rstil build src/examples/hello_script.til --target=windows-x64
	wine ./src/examples/bin/hello_script.exe
	# TODO: macos-x64, macos-arm64 (no emulator available)
	# TODO: wasm32 (needs libc/wasi support)
	@echo "=== All cross-compilation tests passed ==="
