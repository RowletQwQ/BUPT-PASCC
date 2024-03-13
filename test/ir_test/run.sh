#!/bin/bash
set -e
test_dir=../open_set
for file in $test_dir/*; do
    if [ -f $file ]; then
        if [ ${file##*.} = pas ]; then
            echo "Testing $file"
            ../bin/IR_TEST -i $file > $(basename $file).ir
            echo "Testing $file done"
        fi
    fi
done