#!/bin/bash
# Tests for compiled TIL programs using rstil run

set -e

RSTIL="./bin/rstil"

echo "=== Compiled Run Tests ==="

echo "Testing hello_script.til..."
$RSTIL run src/test/hello/hello_script.til
echo "[PASS] hello_script.til"

echo "Testing comparisons.til..."
$RSTIL run src/test/comparisons.til
echo "[PASS] comparisons.til"

echo "Testing circular_test.til..."
$RSTIL run src/test/circular_test.til
echo "[PASS] circular_test.til"

echo "Testing enums_simple.til..."
$RSTIL run src/test/enums_simple.til
echo "[PASS] enums_simple.til"

echo "Testing enums_payload.til..."
$RSTIL run src/test/enums_payload.til
echo "[PASS] enums_payload.til"

echo "=== All Compiled Run Tests Passed! ==="
