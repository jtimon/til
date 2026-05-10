#!/bin/bash
# PreToolUse(Bash) hook: forbid run_in_background:true and backgrounding
# operators in the command itself. See bots/bots.org "Background vs
# Foreground".
input=$(cat)

bg=$(python3 -c "import sys,json; d=json.loads(sys.argv[1]); print(d.get('tool_input',{}).get('run_in_background'))" "$input" 2>/dev/null)
if [ "$bg" = "True" ]; then
    echo "BLOCKED: Bash run_in_background=true is forbidden. Run in the foreground; the Bash tool accepts timeout up to 600000ms." >&2
    exit 2
fi

cmd=$(python3 -c "import sys,json; d=json.loads(sys.argv[1]); print(d.get('tool_input',{}).get('command',''))" "$input" 2>/dev/null)
# Only inspect the first line of the command -- heredoc bodies and
# multi-line string literals on subsequent lines are content, not
# shell-executed code, and matching them produces false positives
# (e.g., a commit message that mentions "nohup" or ends with "&").
first_line=$(printf '%s\n' "$cmd" | head -n1)

# Block trailing & (process backgrounding) but not && or | logical/pipe
# operators.
if echo "$first_line" | grep -qP '(^|[^&])&(\s*$|\s*[;|]|\s*#)'; then
    echo "BLOCKED: trailing '&' backgrounds the command. Run in the foreground." >&2
    exit 2
fi

# Match nohup/disown/setsid only as command starters (start of line or
# after a separator), not as words appearing anywhere in the command.
if echo "$first_line" | grep -qP '(^|[;&|()]|\&\&|\|\|)\s*(nohup|disown|setsid)\b'; then
    echo "BLOCKED: nohup/disown/setsid backgrounds the command. Run in the foreground." >&2
    exit 2
fi
