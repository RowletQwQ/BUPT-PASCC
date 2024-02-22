#!/bin/bash
/usr/share/Pascal2C/build/pascal2c /data/workspace/myshixun/open_set/00_mian.pas /data/workspace/myshixun/open_set/00_mian.c
cd /data/workspace/myshixun/open_set
echo "Please enter filename: "
read filename

gcc $filename
./a.out