#!/bin/bash
# Tests for compiled TIL programs using rstil run

set -e

RSTIL="./bin/rstil"

echo "=== Compiled Run Tests ==="

# TODO: Uncomment when core.til Bool is available via auto-import
# echo "Testing enums_payload.til..."
# $RSTIL run src/test/enums_payload.til
# echo "[PASS] enums_payload.til"

echo "=== All Compiled Run Tests Passed! ==="
