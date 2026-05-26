#!/bin/bash
cmd=$(python3 -c "import sys,json; print(json.load(sys.stdin)['tool_input']['command'])" 2>/dev/null)
# Only inspect the first line of the command -- heredoc bodies and
# multi-line string literals on subsequent lines are content, not
# shell-executed code, and matching them produces false positives
# (e.g., a commit message that mentions "sleep" or "pgrep").
first_line=$(printf '%s\n' "$cmd" | sed -n '1p')

# NOTE: plain echo/cat/head/tail are allowed. They terminate immediately,
# so they never trip the harness auto-background threshold. The Read/Grep
# tools are still preferred for file inspection, but a hard block here only
# created friction (e.g. `tail -n 25 log`, `grep ... | head`, `echo "x"`).
# The genuinely dangerous never-exit form, `tail -f` / `less +F`, is still
# blocked further down.

if echo "$first_line" | grep -qP 'git\s+stash'; then
    echo "BLOCKED: Never use git stash -- it is destructive." >&2
    exit 2
fi

# Forbid polling-as-waiting patterns. These get auto-backgrounded by the
# harness, leaving orphan tasks on its queue that the user has to kill
# by hand. CLAUDE.md "Background vs Foreground" says no -- so do the
# hooks.
if echo "$first_line" | grep -qP '\b(while|until|for)\b[^|;]*\b(pgrep|sleep)\b'; then
    echo "BLOCKED: polling/wait loops (while|until|for ... pgrep|sleep) are forbidden -- they get auto-backgrounded and orphan on the harness queue. Run the command synchronously or skip it." >&2
    exit 2
fi

# Forbid infinite loops with constant conditions. These are pure busy-waits
# and always auto-background past the 120s sandbox threshold.
if echo "$first_line" | grep -qP '\b(while|until)\s+(true|false|:)\b'; then
    echo "BLOCKED: infinite loop (while true / while : / until false) -- gets auto-backgrounded and becomes a Wait ghost task. Skip the wait; the SDK posts a task-notification when the backgrounded command finishes." >&2
    exit 2
fi

# Forbid loops whose body is the no-op ':' command. These too are
# busy-waits in disguise and escape the polling-loop rule above.
if echo "$first_line" | grep -qP '\b(while|until|for)\b[^|]*\bdo\s+:\s*[;\s]'; then
    echo "BLOCKED: busy-wait loop with no-op body (do : ; done) -- gets auto-backgrounded and becomes a Wait ghost task." >&2
    exit 2
fi

# Forbid C-style infinite for (( ; ; ))
if echo "$first_line" | grep -qP '\bfor\s*\(\(\s*;\s*;\s*\)\)'; then
    echo "BLOCKED: C-style infinite for (( ; ; )) -- gets auto-backgrounded and becomes a Wait ghost task." >&2
    exit 2
fi

# Forbid tail -f (and similar follow flags) -- these never exit and get
# auto-backgrounded. tail itself is already blocked above, but be explicit.
if echo "$first_line" | grep -qP '\b(tail|less|more)\s+[^|;]*-[fF]'; then
    echo "BLOCKED: 'tail -f' / 'less +F' never exit and get auto-backgrounded. Read the log file directly with the Read tool." >&2
    exit 2
fi

if echo "$first_line" | grep -qP '\bpgrep\b'; then
    echo "BLOCKED: 'pgrep' is forbidden -- it's only used here for polling/waiting, which leaves orphan tasks. Run the command synchronously or skip it." >&2
    exit 2
fi

if echo "$first_line" | grep -qP '\bsleep\s+[0-9]'; then
    echo "BLOCKED: 'sleep N' is forbidden -- it's a wait. The Bash tool already blocks until the command finishes. Don't add waits." >&2
    exit 2
fi
