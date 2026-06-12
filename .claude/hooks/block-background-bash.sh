#!/bin/bash
# PreToolUse(Bash) hook: enforce ONE long-running task at a time.
#
# Background: Claude Code Web auto-backgrounds any foreground bash
# exceeding the hardcoded ~120s sandbox timeout (Anthropic Issue
# #11716, #58662, #59900). When a Claude session keeps issuing tool
# calls while a previous build/test is still auto-backgrounded, the
# old task lingers as a Wait ghost in the sidebar with no way to
# dismiss it -- ghost tasks accumulate ("a million background tasks
# again, half of them for waiting") and the human has to hand-kill
# everything.
#
# This hook makes that impossible at the source:
#   1. Reject any explicit run_in_background=true.
#   2. Reject any trailing & / nohup / disown / setsid.
#   3. Reject ANY new Bash call when a long-running task (make, cc,
#      bin/til, gdb, ...) from a previous tool call is still alive.
# The Claude turn ends after the rejection; the SDK's task-notification
# wakes the session once the existing job actually finishes.
input=$(cat)

bg=$(python3 -c "import sys,json; d=json.loads(sys.argv[1]); print(d.get('tool_input',{}).get('run_in_background'))" "$input" 2>/dev/null)
cmd=$(python3 -c "import sys,json; d=json.loads(sys.argv[1]); print(d.get('tool_input',{}).get('command',''))" "$input" 2>/dev/null)
# Only inspect the first line of the command -- heredoc bodies and
# multi-line string literals on subsequent lines are content, not
# shell-executed code, and matching them produces false positives
# (e.g., a commit message that mentions "nohup" or ends with "&").
first_line=$(printf '%s\n' "$cmd" | sed -n '1p')

if [ "$bg" = "True" ]; then
    echo "BLOCKED: run_in_background=true creates a ghost task entry that can't be dismissed from the sidebar (Anthropic Issue #58662, #59900). Run synchronously; the harness auto-backgrounds long bash anyway, and the in-flight check below prevents a second call from stacking on top." >&2
    exit 2
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

# Universal one-task-at-a-time guard:
#
# Walk every process on the system and look for long-running tasks
# that match the kinds the harness auto-backgrounds. If one is alive
# AND it isn't an ancestor / sibling of THIS hook's process tree
# (i.e., it's a leftover from a previous tool call), refuse the new
# Bash call.
#
# Patterns checked (extend the regex when new long jobs land):
#   - GNU make
#   - gcc/cc/clang compile drivers
#   - bin/til, bin/til_boot, bin/til_asan, bin/til_debug
#   - gdb (long batch runs)
self_pgid=$(awk '{print $5}' /proc/$$/stat 2>/dev/null)
# The managed runner's own subcommands (status/kill) are the HANDLE for
# the one sanctioned long job -- blocking them deadlocks the session
# against its own job (the hook refuses every call while the job lives,
# including the call that would kill it). Always let them through; they
# are instant and never start work.
case "$first_line" in
    .claude/hooks/managed-run.sh*) exit 0 ;;
esac
match_regex='(^|[/[:space:]])(make|cc|gcc|clang|gdb|bin/til|bin/til_boot|bin/til_asan|bin/til_debug)([[:space:]]|$)'

for cmdline_file in /proc/[0-9]*/cmdline; do
    [ -r "$cmdline_file" ] || continue
    pid_dir=${cmdline_file%/cmdline}
    pid=${pid_dir#/proc/}
    # Skip our own process and our direct shell parent (the hook tree).
    [ "$pid" = "$$" ] && continue
    [ "$pid" = "$PPID" ] && continue
    other_pgid=$(awk '{print $5}' "/proc/$pid/stat" 2>/dev/null)
    # Skip anything in the same process group as the hook (its own
    # forks: the python invocations above, etc).
    [ -n "$self_pgid" ] && [ "$other_pgid" = "$self_pgid" ] && continue
    # cmdline is NUL-separated; convert to spaces for grep.
    other_cmdline=$(tr '\0' ' ' < "$cmdline_file" 2>/dev/null)
    if echo "$other_cmdline" | grep -qE "$match_regex"; then
        offender=$(echo "$other_cmdline" | head -c 120)
        echo "BLOCKED: a long-running task from a previous tool call is still alive (pid $pid: ${offender}...). End this turn and wait for the SDK's task-notification before issuing the next Bash call -- piling on top creates the 'wait for make / build' ghost tasks that accumulate in the sidebar." >&2
        exit 2
    fi
done
