#!/bin/bash
set -e

CTIL=bin/ctil
TESTS="src/test/types.til src/test/operators.til src/test/functions.til src/test/structs.til src/test/optional_args.til src/test/forward_refs.til src/test/flow.til src/test/strings.til src/test/ref.til src/test/own_fields.til src/test/macros.til src/test/enums.til src/test/vecs.til src/test/arrays.til src/test/sets.til src/test/maps.til src/test/misc.til"
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

if [ $FAIL -eq 0 ]; then
    echo "all tests passed"
fi
exit $FAIL
