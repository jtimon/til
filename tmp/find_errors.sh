#!/bin/bash
./bin/rstil src/core/self/init.til 2>&1 | grep "Could not find function" | \
  sed 's/.*init.til:\([0-9]*\).*/\1/' | sort -u -n | while read line; do
  if [ -n "$line" ]; then
    echo "Line $line: $(sed -n "${line}p" src/core/self/init.til | sed 's/^[[:space:]]*//')"
  fi
done
