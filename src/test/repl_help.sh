#!/bin/sh
# REPL help() smoke test for #157 Phase 1.
#
# Single REPL turn that exercises help() once and exits. The test
# runner counts the expected core doc text in the merged stdout. The
# rest of the help() surface (function signatures, var types, struct
# multi-line listing, undefined-symbol diagnostic) is exercised
# interactively; a richer per-feature test multiplies REPL cost
# unacceptably because each turn re-parses the typed program.
printf 'help("println")\n' | bin/til
