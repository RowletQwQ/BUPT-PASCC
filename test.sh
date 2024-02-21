#!/bin/bash
cd /data/workspace/myshixun/hidden_set
echo "Please enter filename: "
read filename

gcc $filename
./a.out