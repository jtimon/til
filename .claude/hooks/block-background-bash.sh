#!/bin/bash
# PreToolUse(Bash) hook: control run_in_background to allow at most one
# background `make` task at a time, and forbid all other backgrounding.
# Rationale: Claude Code Web auto-backgrounds any foreground bash exceeding
# the hardcoded ~120s sandbox timeout (Issue #11716, #58662 etc), and
# ghost task entries accumulate in the sidebar with no way to dismiss
# them. The only safe pattern is ONE intentional background `make`
# call per turn, then end the turn and wait for the SDK's
# <task-notification> to wake the session. No polling, no Wait tasks.
input=$(cat)

bg=$(python3 -c "import sys,json; d=json.loads(sys.argv[1]); print(d.get('tool_input',{}).get('run_in_background'))" "$input" 2>/dev/null)
cmd=$(python3 -c "import sys,json; d=json.loads(sys.argv[1]); print(d.get('tool_input',{}).get('command',''))" "$input" 2>/dev/null)
# Only inspect the first line of the command -- heredoc bodies and
# multi-line string literals on subsequent lines are content, not
# shell-executed code, and matching them produces false positives
# (e.g., a commit message that mentions "nohup" or ends with "&").
first_line=$(printf '%s\n' "$cmd" | sed -n '1p')

if [ "$bg" = "True" ]; then
    # Only allow background mode for `make` commands (typically `make test`
    # or `git reset --soft ... && make ...`). Everything else must be
    # foreground -- if it takes longer than 120s, the harness will warn
    # us via auto-background, but for short commands foreground is
    # correct and clean.
    if ! echo "$first_line" | grep -qP '(^|&&\s*)\s*(make|git\s+reset\s+--soft[^&]*&&\s*make)\b'; then
        echo "BLOCKED: run_in_background=true is only allowed for 'make' commands. The harness auto-backgrounds long foreground bash anyway; deliberately backgrounding other commands creates ghost task entries that can't be dismissed from the sidebar (Anthropic Issue #58662, #59900)." >&2
        exit 2
    fi

    # Only one background `make` at a time. Check /proc/*/cmdline for any
    # running `make` process. Skip our own process tree.
    self_pgid=$(cat /proc/$$/stat 2>/dev/null | awk '{print $5}')
    for cmdline_file in /proc/[0-9]*/cmdline; do
        [ -r "$cmdline_file" ] || continue
        pid_dir=${cmdline_file%/cmdline}
        pid=${pid_dir#/proc/}
        # Skip our own process and its parents (the hook's own bash tree)
        [ "$pid" = "$$" ] && continue
        [ "$pid" = "$PPID" ] && continue
        # Compare process group id; skip if same as ours (sibling of hook)
        other_pgid=$(awk '{print $5}' "/proc/$pid/stat" 2>/dev/null)
        [ -n "$self_pgid" ] && [ "$other_pgid" = "$self_pgid" ] && continue
        # cmdline is NUL-separated; convert to spaces for grep
        if tr '\0' ' ' < "$cmdline_file" 2>/dev/null | grep -qE '(^|[/[:space:]])make([[:space:]]|$)'; then
            echo "BLOCKED: a 'make' process is already running (pid $pid). Only one background 'make' is allowed at a time -- wait for the SDK <task-notification> indicating completion before launching another." >&2
            exit 2
        fi
    done
fi

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
