#!/bin/bash
# PreToolUse(Bash) hook: refuse shell-level backgrounding.
#
# CLAUDE_CODE_DISABLE_BACKGROUND_TASKS=1 in .claude/settings.json
# removes the run_in_background parameter and makes a command that
# reaches its timeout stop instead of moving to the background, so
# Claude Code itself never leaves a background task behind. What the
# setting cannot stop is the shell backgrounding a process on its own:
# a trailing & or nohup/disown/setsid returns at once and leaves an
# untracked orphan. Permission deny rules match command prefixes and
# cannot see a trailing &, so this one check stays a hook.
cmd=$(python3 -c "import sys,json; print(json.load(sys.stdin).get('tool_input',{}).get('command',''))" 2>/dev/null)
# Only inspect the first line of the command -- heredoc bodies and
# multi-line string literals on subsequent lines are content, not
# shell-executed code, and matching them produces false positives
# (e.g., a commit message that mentions "nohup" or ends with "&").
first_line=$(printf '%s\n' "$cmd" | sed -n '1p')

# Block trailing & (process backgrounding), including inside a subshell
# like (cmd &), but not && or | logical/pipe operators.
if echo "$first_line" | grep -qP '(^|[^&])&(\s*$|\s*[;|)]|\s*#)'; then
    echo "BLOCKED: trailing '&' backgrounds the command. Run in the foreground." >&2
    exit 2
fi

# Match nohup/disown/setsid only as command starters (start of line or
# after a separator), not as words appearing anywhere in the command.
if echo "$first_line" | grep -qP '(^|[;&|()]|\&\&|\|\|)\s*(nohup|disown|setsid)\b'; then
    echo "BLOCKED: nohup/disown/setsid backgrounds the command. Run in the foreground." >&2
    exit 2
fi
