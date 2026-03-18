#!/bin/bash
cmd=$(python3 -c "import sys,json; print(json.load(sys.stdin)['tool_input']['command'])" 2>/dev/null)
if echo "$cmd" | grep -qP '(^|[|;&])\s*(echo|cat|head|tail)\b'; then
    echo "BLOCKED: Use Read/Write/Grep tools instead of echo/cat/head/tail" >&2
    exit 2
fi

if echo "$cmd" | grep -qP 'git\s+(restore|stash)'; then
    echo "BLOCKED: Never use git restore or git stash — these are destructive." >&2
    exit 2
fi
