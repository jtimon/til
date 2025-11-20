#!/usr/bin/env python3
"""Add cleanup before all return statements in eval_user_func_proc_call"""

import re

# Read the file
with open('src/rs/interpreter.rs', 'r') as f:
    lines = f.readlines()

# Process lines 2525-3195 (the function)
output_lines = []
i = 0

while i < len(lines):
    line = lines[i]
    line_num = i + 1

    # Only process lines in the function range
    if 2525 <= line_num <= 3195:
        # Check if this line contains a return statement
        stripped = line.lstrip()
        if stripped.startswith('return '):
            # Get the indentation
            indent = line[:len(line) - len(stripped)]
            # Add cleanup before the return
            cleanup = indent + 'context.pop_function_scope(saved_path)?;\n'
            output_lines.append(cleanup)

    output_lines.append(line)
    i += 1

# Write back
with open('src/rs/interpreter.rs', 'w') as f:
    f.writelines(output_lines)

print("Added cleanup before all return statements")
