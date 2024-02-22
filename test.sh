#!/bin/bash
cd /data/workspace/myshixun/open_set
for file in *.pas; do
    /usr/share/Pascal2C/build/pascal2c  "$file" "${file%.pas}.c"
done
#/usr/share/Pascal2C/build/pascal2c 00_main.pas 00_main.c

read filename

gcc $filename
./a.out