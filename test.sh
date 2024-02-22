#!/bin/bash
cd /data/workspace/myshixun/open_set
/usr/share/Pascal2C/build/pascal2c 00_mian.pas 00_mian.c
echo "Please enter filename: "
read filename

gcc $filename
./a.out