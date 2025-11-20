#!/usr/bin/env python3
"""
Refactor eval_user_func_proc_call to use scope push/pop instead of context cloning.
"""

import re
import sys

def refactor_function(content):
    """Refactor the eval_user_func_proc_call function"""

    # Find the function (lines 2525-3192 approximately)
    lines = content.split('\n')

    # Step 1: Replace context.clone() with scope push (around line 2543)
    for i in range(2520, 2550):
        if i >= len(lines):
            break
        if 'let mut function_context = context.clone();' in lines[i]:
            lines[i] = '    // REFACTORED: Replaced context.clone() with scope push/pop'
            lines[i+1] = '    // This uses the scope stack instead of cloning the entire context (~68-247 KB per call)'
            lines[i+2] = '    let saved_path = context.push_function_scope(&func_def.source_path);'
            # Remove the path assignment line
            if 'function_context.path = func_def.source_path' in lines[i+3]:
                del lines[i+3]
            # Remove all the TODO comment lines above
            j = i - 1
            while j > 2520 and '// TODO REFACTOR' in lines[j] or '// When refactoring' in lines[j] or '// 1.' in lines[j] or '// 2.' in lines[j] or '// 3.' in lines[j] or '// 4.' in lines[j] or '//' in lines[j] and '///' not in lines[j] and 'REM' not in lines[j]:
                if lines[j].strip().startswith('//') and 'Return paths requiring cleanup' not in lines[j]:
                    del lines[j]
                    i -= 1
                else:
                    break
                j -= 1
            break

    # Step 2: Replace all function_context with context (lines 2525-3195)
    for i in range(2520, min(3200, len(lines))):
        lines[i] = lines[i].replace('function_context', 'context')

    # Step 3: Add cleanup before all return statements in the function
    # Find all returns between lines 2525 and 3195
    i = 2524
    while i < min(3200, len(lines)):
        line = lines[i]
        # Check if this is a return statement
        if re.search(r'^\s+return\s+(Ok|Err)\(', line):
            # Add cleanup before it
            indent = len(line) - len(line.lstrip())
            cleanup_line = ' ' * indent + 'context.pop_function_scope(saved_path)?;'
            lines.insert(i, cleanup_line)
            i += 1  # Skip the line we just inserted
        i += 1

    return '\n'.join(lines)

def main():
    input_file = sys.argv[1]
    output_file = sys.argv[2]

    with open(input_file, 'r') as f:
        content = f.read()

    refactored = refactor_function(content)

    with open(output_file, 'w') as f:
        f.write(refactored)

    print(f"Refactored {input_file} -> {output_file}")

if __name__ == '__main__':
    main()
