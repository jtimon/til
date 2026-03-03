#!/bin/bash
set -e

CTIL=bin/ctil
TESTS="src/test/misc.til src/test/structs.til src/test/optional_args.til src/test/forward_refs.til src/test/arithmetics.til"
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
if [ "$errors" -ne 25 ]; then
    echo "FAIL: typer_errors expected 25 errors, got $errors"
    FAIL=1
fi

if [ $FAIL -eq 0 ]; then
    echo "all tests passed"
fi
exit $FAIL
