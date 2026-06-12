#!/bin/bash
# Managed detached runner for >120s commands in remote sessions.
#
# The cloud harness converts any long FOREGROUND tool call into a
# sidebar task entry that is never reaped (verified exhaustively
# 2026-06-12). Detached jobs are the ONLY shape that creates ZERO
# entries. The wake-up problem is solved by the stop-hook: `start`
# drops an untracked marker file (JOB_RUNNING) in the repo root, so
# the tree is not clean and the stop-hook pokes the session after
# every ended turn; each poke costs one instant `status` call. The
# job's epilogue removes the marker, so pokes stop when it is done.
#
#   start <cmd...>  detach job (setsid, own pgroup), pid in tmp/job.pid,
#                   log in tmp/job.log, exit code in tmp/job.done,
#                   marker JOB_RUNNING in repo root. Refuses if live.
#   status          instant: RUNNING pid / DONE exit + log tail
#   kill            group-kill, escalate, verify empty, clean marker
#
# Session discipline: ONE managed job at a time; NEVER run any other
# command while it runs except `status`.

set -u
PID_FILE=tmp/job.pid
LOG_FILE=tmp/job.log
DONE_FILE=tmp/job.done
CMD_FILE=tmp/job.cmd
MARKER=JOB_RUNNING
mkdir -p tmp

job_alive() {
    [ -f "$PID_FILE" ] || return 1
    local pid
    pid=$(cat "$PID_FILE" 2>/dev/null) || return 1
    [ -n "$pid" ] && kill -0 "$pid" 2>/dev/null
}

case "${1:-}" in
start)
    shift
    [ $# -ge 1 ] || { echo "usage: managed-run.sh start <cmd...>"; exit 1; }
    if job_alive; then
        echo "REFUSED: job pid $(cat "$PID_FILE") still running: $(cat "$CMD_FILE" 2>/dev/null)"
        exit 1
    fi
    rm -f "$DONE_FILE" "$PID_FILE"
    printf '%s\n' "$*" > "$CMD_FILE"
    : > "$LOG_FILE"
    echo "managed job running -- see tmp/job.log; this marker is removed by the job itself" > "$MARKER"
    setsid bash -c "{ $* ; } > '$LOG_FILE' 2>&1; echo \$? > '$DONE_FILE'; rm -f '$MARKER'" < /dev/null &
    echo $! > "$PID_FILE"
    echo "STARTED pid $(cat "$PID_FILE"): $*"
    ;;
status)
    if [ -f "$DONE_FILE" ]; then
        echo "DONE exit=$(cat "$DONE_FILE") cmd: $(cat "$CMD_FILE" 2>/dev/null)"
        tail -n 5 "$LOG_FILE" 2>/dev/null
    elif job_alive; then
        echo "RUNNING pid $(cat "$PID_FILE") cmd: $(cat "$CMD_FILE" 2>/dev/null)"
        tail -n 2 "$LOG_FILE" 2>/dev/null
    else
        rm -f "$MARKER"
        echo "NO JOB"
    fi
    ;;
kill)
    if [ -f "$PID_FILE" ]; then
        pid=$(cat "$PID_FILE")
        kill -- -"$pid" 2>/dev/null || kill "$pid" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do
            pkill -9 -g "$pid" 2>/dev/null
            pgrep -g "$pid" > /dev/null 2>&1 || break
            sleep 0.5
        done
        if pgrep -g "$pid" > /dev/null 2>&1; then
            echo "WARNING: group $pid still alive:"; pgrep -g "$pid" -l
        else
            echo "KILLED pid $pid (group empty, verified)"
        fi
        rm -f "$PID_FILE" "$MARKER"
    else
        echo "NO JOB to kill"
    fi
    ;;
*)
    echo "usage: managed-run.sh start <cmd...> | status | kill"
    exit 1
    ;;
esac
