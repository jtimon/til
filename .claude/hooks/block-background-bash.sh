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
input=$(cat)

# Reduce the command to the text the shell executes, on every line:
# heredoc bodies, quoted strings and comments are content, not code,
# and matching them produces false positives (e.g., a commit message
# that mentions "nohup" or ends with "&"). Quoted strings become an
# empty pair, comments and heredoc bodies are dropped, and an escaped
# character becomes a placeholder.
scan=$(python3 - "$input" <<'PY'
import json, re, sys
cmd = json.loads(sys.argv[1]).get('tool_input', {}).get('command', '')
heredoc_re = re.compile(r'<<(-?)\s*([\'"]?)([A-Za-z_]\w*)\2')
out = []
heredocs = []
i, n = 0, len(cmd)
while i < n:
    c = cmd[i]
    if c == '\n':
        out.append(c)
        i += 1
        for strip_tabs, delim in heredocs:
            while i < n:
                j = cmd.find('\n', i)
                if j < 0:
                    j = n
                line = cmd[i:j]
                i = j + 1
                if (line.lstrip('\t') if strip_tabs else line) == delim:
                    break
        heredocs = []
        continue
    if c == '\\':
        if cmd[i + 1:i + 2] != '\n':
            out.append('_')
        i += 2
        continue
    if c in '\'"':
        j = i + 1
        while j < n and cmd[j] != c:
            if c == '"' and cmd[j] == '\\':
                j += 1
            j += 1
        out.append(c + c)
        i = j + 1
        continue
    if c == '#' and (i == 0 or cmd[i - 1] in ' \t\n;&|()'):
        j = cmd.find('\n', i)
        i = n if j < 0 else j
        continue
    if cmd.startswith('<<', i) and not cmd.startswith('<<<', i):
        m = heredoc_re.match(cmd, i)
        if m:
            heredocs.append((m.group(1) == '-', m.group(3)))
            out.append(m.group(0))
            i = m.end()
            continue
    out.append(c)
    i += 1
print(''.join(out))
PY
)

# Block trailing & (process backgrounding), including inside a subshell
# like (cmd &), but not && or | logical/pipe operators.
if printf '%s\n' "$scan" | grep -qP '(^|[^&])&(\s*$|\s*[;|)])'; then
    echo "BLOCKED: trailing '&' backgrounds the command. Run in the foreground." >&2
    exit 2
fi

# Match nohup/disown/setsid only as command starters (start of line,
# after a separator, or after then/do/else), not as words appearing
# anywhere in the command.
if printf '%s\n' "$scan" | grep -qP '(^|[;&|(){]|\b(then|do|else)\b)\s*(nohup|disown|setsid)\b'; then
    echo "BLOCKED: nohup/disown/setsid backgrounds the command. Run in the foreground." >&2
    exit 2
fi
