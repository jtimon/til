.PHONY: all tests repl til clean
all: rstil

clean:
	rm -rf bin/* gen/*

# REPL = Read-Eval-Print-Loop
repl: rstil
	rlwrap ./bin/rstil src/core/repl.til

rstil: src/rstil.rs
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

# TODO Self hosting
til: rstil
	timeout 10 ./bin/rstil build src/til.til
	@cp gen/c/til.c bootstrap/til.c 2>/dev/null || true
	# timeout 10 ./bin/til build src/til.til

tests: rstil til
	timeout 90 ./bin/rstil src/tests.til
	@cp gen/c/test/constfold.c src/test/constfold.c 2>/dev/null || true
	@echo "Remember to add generated files to commit: bootstrap/til.c, src/test/constfold.c, doc/benchmark.org"

test-cross: rstil til
	@echo "=== Cross-compilation tests ==="
	@echo "linux-arm64..."
	timeout 90 ./bin/rstil build src/examples/hello_script.til --target=linux-arm64
	timeout 90 qemu-aarch64 -L /usr/aarch64-linux-gnu ./src/examples/bin/hello_script
	@echo "linux-riscv64..."
	timeout 90 ./bin/rstil build src/examples/hello_script.til --target=linux-riscv64
	timeout 90 qemu-riscv64 -L /usr/riscv64-linux-gnu ./src/examples/bin/hello_script
	@echo "windows-x64..."
	timeout 90 ./bin/rstil build src/examples/hello_script.til --target=windows-x64
	timeout 90 wine ./src/examples/bin/hello_script.exe
	# TODO: macos-x64, macos-arm64 (no emulator available)
	# TODO: wasm32 (needs libc/wasi support)
	@echo "=== All cross-compilation tests passed ==="
