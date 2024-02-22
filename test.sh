#!/bin/bash
cd /data/workspace/myshixun/hidden_set
/usr/share/Pascal2C/build/pascal2c 00_main.pas 00_main.c

read filename

gcc $filename
./a.out