.PHONY: all tests repl til clean copy_gen
all: rstil

rstil: src/rstil.rs
	@mkdir -p bin
	rustc src/rstil.rs -o bin/rstil

tests: rstil
	@mkdir -p tmp
	./bin/rstil src/tests.til

# TODO run src/til.til with til.til
til: rstil tests
	./bin/rstil interpret src/til.til src/test/self/lexer/premode.til
	# ./bin/rstil interpret src/til.til help
	# ./bin/rstil interpret src/til.til src/test/strings.til
	# ./bin/rstil interpret src/til.til src/core/lexer.til

# REPL = Read-Eval-Print-Loop
repl: rstil
	rlwrap ./bin/rstil src/core/repl.til

test-cross: rstil
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

clean:
	rm -rf bin/* gen/*

copy_gen:
	@echo "Copying generated files to tracked locations..."
	@mkdir -p bootstrap
	cp gen/c/til.c bootstrap/til.c
	cp gen/benchmark.org doc/benchmark.org
	@echo "Done. You can now commit these files."
