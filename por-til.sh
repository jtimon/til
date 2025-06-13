#!/bin/bash

# 1. Rename *.til files to *.til
find . -type f -name "*.til" | while read -r file; do
  newfile="${file%.til}.til"
  echo "Renaming file: $file -> $newfile"
  mv "$file" "$newfile"
done

# 2. Replace 'til' in all casing variants with 'til', preserving original casing
find . -type f ! -path '*/.git/*' | while read -r file; do
  if file "$file" | grep -q text; then
    echo "Replacing content in: $file"
    python3 -c "
import re
from pathlib import Path

def repl(match):
    word = match.group()
    result = ''.join(
        t.upper() if c.isupper() else t.lower()
        for c, t in zip(word, 'til')
    )
    return result

p = Path('$file')
text = p.read_text(encoding='utf-8', errors='ignore')
text = re.sub(r'(?i)\bcil\b', repl, text)
p.write_text(text, encoding='utf-8')
"
  fi
done
