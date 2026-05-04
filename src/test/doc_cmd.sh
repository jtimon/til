#!/bin/sh
# Smoke test for `til doc <path>` (issue #157 Phase 2). Runs the doc
# generator on the self-host source itself, then verifies a few key
# pages landed under doc/gen/ with their expected /// text and signatures.
rm -rf doc/gen
bin/til doc src/til.til > /dev/null 2>&1
test -f doc/gen/src/til.org || exit 1
test -f doc/gen/src/core/vec.org || exit 1
test -f doc/gen/src/core/set.org || exit 1
test -f doc/gen/src/self/parser.org || exit 1
grep -q "Unordered collection of unique typed elements" doc/gen/src/core/set.org || exit 1
grep -q "func add(mut self: Set, own val: Dynamic)" doc/gen/src/core/set.org || exit 1
grep -q "* main" doc/gen/src/til.org || exit 1
echo doc_cmd_ok
