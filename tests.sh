#!/bin/bash
set -e

CTIL=bin/ctil
TESTS="src/test/types.til src/test/operators.til src/test/functions.til src/test/structs.til src/test/optional_args.til src/test/forward_refs.til src/test/flow.til"
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

# typer_errors: should fail with exactly 25 errors
errors=$($CTIL interpret src/test/typer_errors.til 2>&1 | grep -c "type error:" || true)
if [ "$errors" -ne 32 ]; then
    echo "FAIL: typer_errors expected 32 errors, got $errors"
    FAIL=1
fi

if [ $FAIL -eq 0 ]; then
    echo "all tests passed"
fi
exit $FAIL
