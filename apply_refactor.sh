#!/bin/bash
set -e

FILE="src/rs/interpreter.rs"

# Step 1: Replace the clone block with scope push
sed -i '2526,2544s|    // TODO REFACTOR.*|    // REFACTORED: Replaced context.clone() with scope push/pop|' "$FILE"
sed -i '2527,2544d' "$FILE"
sed -i '2526a\    // This uses the scope stack instead of cloning the entire context (~68-247 KB per call)\n    let saved_path = context.push_function_scope(&func_def.source_path);' "$FILE"

# Step 2: Replace function_context with context in the function (lines 2525-3195)
sed -i '2525,3195s/function_context/context/g' "$FILE"

# Step 3: Add cleanup before returns - we'll need to do this more carefully
# For now, let's just compile and see what errors we get

echo "Basic refactoring applied. Now need to add cleanup before returns."
