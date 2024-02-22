#!/bin/bash
cd /data/workspace/myshixun/open_set
rm a.out
#/usr/share/Pascal2C/build/pascal2c 00_main.pas 00_main.c

read filename

if [ ! -e "$filename" ]; then
    cd /data/workspace/myshixun/hidden_set
    rm a.out
    if [ ! -e "$filename" ]; then
        echo "File does not exist."
        exit
    fi
fi

gcc $filename
./a.out