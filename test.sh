#!/bin/bash
cd /data/workspace/myshixun/open_set
echo "Please enter filename: "
read filename

gcc $filename
./a.out