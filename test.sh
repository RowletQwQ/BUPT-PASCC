#!/bin/bash
/usr/share/Pascal2C/build/pascal2c /data/workspace/myshixun/hidden_set/00_comment2.pas /data/workspace/myshixun/hidden_set/00_comment2.c
cd /data/workspace/myshixun/hidden_set
read filename

gcc $filename
./a.out