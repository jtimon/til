.PHONY: all tests repl til clean benchmark
all: rstil

clean:
	rm -rf bin/* gen/*

# REPL = Read-Eval-Print-Loop
repl: rstil
	rlwrap ./bin/rstil repl

rstil: src/rstil.rs
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

# TODO Self hosting
til: rstil
	./bin/rstil build src/til.til
	@cp gen/c/til.c bootstrap/til.c 2>/dev/null || true
	# ./bin/til build src/til.til

tests: rstil
	./bin/rstil interpret src/tests.til
	@cp gen/c/test/constfold.c src/test/constfold.c 2>/dev/null || true
	@echo "Remember to add generated files to commit: bootstrap/til.c, src/test/constfold.c"

regen: rstil til
	./bin/rstil interpret src/tests.til regen
	@echo "Regenerated all test outputs"

benchmark: tests
	@cp gen/benchmark.org doc/benchmark.org
	@echo "Benchmark saved to doc/benchmark.org, can be committed"

test-cross: rstil til
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
