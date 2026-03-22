---
name: debug
description: Debug a build/test failure by reading the actual error output
user-invocable: true
---

# Debug a build/test failure

When a build or test fails, follow these steps IN ORDER. Do NOT skip steps.

## Step 1: Read the FULL error

```bash
Read tmp/build.log
```

Read the ENTIRE file. Not grep. Not head. Not the first 10 lines. THE WHOLE FILE.

## Step 2: Identify the error

Write down in plain text:
- The exact error message(s)
- The file(s) and line number(s)
- Which compilation pass failed (til_boot pass 1, til pass 2, link, test run)

## Step 3: Read the offending line(s)

Use the Read tool to read the file and line mentioned in the error.

## Step 4: Understand the error

Explain what the error means. Not what you think it might be. What it ACTUALLY says.

## Step 5: Fix

Only NOW propose or make a fix. The fix must address the ACTUAL error, not a guess.

## Rules

- NEVER revert changes as a response to an error. Debug forward.
- NEVER guess what the error is. READ IT.
- NEVER retry the build hoping it works. Understand first, fix second.
- If the error is in generated code (gen/ or boot/), trace it back to the .til or .c source.
- If you don't understand the error, say so. Don't fake it.
