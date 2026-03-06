#!/bin/bash
set -e

CTIL=bin/ctil
TESTS="src/test/types.til src/test/operators.til src/test/functions.til src/test/structs.til src/test/optional_args.til src/test/forward_refs.til src/test/flow.til src/test/strings.til src/test/ref.til src/test/own_fields.til src/test/macros.til src/test/enums.til src/test/vecs.til src/test/arrays.til src/test/sets.til src/test/maps.til src/test/globals.til src/test/globals_cli.til src/test/misc.til src/test/array_lit.til src/test/cmp.til"
FAIL=0

for t in $TESTS; do
    name=$(basename "$t" .til)
    if ! $CTIL interpret "$t" > /dev/null 2>&1; then
        echo "FAIL (interpret): $name"
        FAIL=1
    fi
    if ! $CTIL run "$t" > /dev/null 2>&1; then
        echo "FAIL (codegen):   $name"
        FAIL=1
    fi
done

# FFI + ext_struct tests: codegen only (interpreter lacks struct marshaling for FFI, see #1)
FFI_TESTS="src/examples/ffi/ext_module.til"
for t in $FFI_TESTS; do
    name=$(basename "$t" .til)
    expected="hello world
hello universe"
    got=$($CTIL run "$t" 2>&1)
    if [ "$got" != "$expected" ]; then
        echo "FAIL (codegen):   ffi/$name"
        echo "  expected: $expected"
        echo "  got:      $got"
        FAIL=1
    fi
done

# typer_errors: should fail with exactly 25 errors
errors=$($CTIL interpret src/test/typer_errors.til 2>&1 | grep -c "type error:" || true)
if [ "$errors" -ne 36 ]; then
    echo "FAIL: typer_errors expected 36 errors, got $errors"
    FAIL=1
fi

# CLI args tests: check output and exit codes for both interpret and codegen
cli_test() {
    local file="$1" expected="$2" exit_expected="$3"
    shift 3
    local name=$(basename "$file" .til)

    got=$($CTIL interpret "$file" "$@" 2>&1) && rc=0 || rc=$?
    if [ "$rc" -ne "$exit_expected" ]; then
        echo "FAIL (interpret): cli/$name (exit $rc, expected $exit_expected)"
        FAIL=1
    elif [ "$exit_expected" -eq 0 ] && [ "$got" != "$expected" ]; then
        echo "FAIL (interpret): cli/$name"
        echo "  expected: $expected"
        echo "  got:      $got"
        FAIL=1
    fi

    got=$($CTIL run "$file" "$@" 2>&1) && rc=0 || rc=$?
    if [ "$rc" -ne "$exit_expected" ]; then
        echo "FAIL (codegen):   cli/$name (exit $rc, expected $exit_expected)"
        FAIL=1
    elif [ "$exit_expected" -eq 0 ] && [ "$got" != "$expected" ]; then
        echo "FAIL (codegen):   cli/$name"
        echo "  expected: $expected"
        echo "  got:      $got"
        FAIL=1
    fi
}

cli_test src/examples/cli_args.til "hello
world" 0 hello world
cli_test src/examples/cli_args.til "" 0
cli_test src/examples/cli_typed.til "alice 42" 0 alice 42
cli_test src/examples/hello_cli.til "Hello World!" 0
cli_test src/examples/cli_variadic_i64.til "60" 0 add 10 20 30
cli_test src/examples/cli_variadic_i64.til "24" 0 mul 2 3 4
cli_test src/examples/cli_variadic_i64.til "0" 0 add
cli_test src/examples/cli_variadic_bool.til "false" 0 true true false
cli_test src/examples/cli_variadic_bool.til "true" 0 true true
# Error cases (nonzero exit)
cli_test src/examples/cli_typed.til "" 1 alice
cli_test src/examples/cli_typed.til "" 1 a b c
cli_test src/examples/hello_cli.til "" 1 extra

if [ $FAIL -eq 0 ]; then
    echo "all tests passed"
fi
exit $FAIL
