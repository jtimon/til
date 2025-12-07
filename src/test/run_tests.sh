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

echo "=== All Compiled Run Tests Passed! ==="
