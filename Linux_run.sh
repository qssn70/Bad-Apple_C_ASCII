#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
dir="$SCRIPT_DIR/frames-ascii" 

for filename in $(ls -v "$dir"); do
    file="$dir/$filename"
    if [ -f "$file" ]; then
        cat "$file"
    fi
    sleep 0.024
done

