#!/bin/bash

function get_char()
{
  SAVEDSTTY=`stty -g`
  stty -echo
  stty cbreak
  dd if=/dev/tty bs=1 count=1 2> /dev/null
  stty -raw
  stty echo
  stty $SAVEDSTTY
}

enable_pause=1

function pause()
{
  if [ "x$1" != "x" ]; then
    echo $1
  fi
  if [ $enable_pause -eq 1 ]; then
    echo "按下任意键继续!"
    char=`get_char`
  fi
}

resize -s 37 97 || echo "！！自动调整窗口大小出错！！" && echo "请手动调整窗口大小至宽97高37以获得更好的效果" && echo "调整完成后按下任意键继续" && pause

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
dir="$SCRIPT_DIR/frames-ascii" 

for filename in $(ls -v "$dir"); do
    file="$dir/$filename"
    if [ -f "$file" ]; then
        cat "$file"
    fi
    sleep 0.024
done

