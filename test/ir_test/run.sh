#!/bin/bash
test_dir=../open_set
exit_status=0
for file in $test_dir/*; do
    if [ -f $file ]; then
        if [ ${file##*.} = pas ]; then
            echo "Testing $file"
            ../bin/IR_TEST -i $file -d 4 > $(basename $file).ir || exit_status=$?
            echo "Testing $file done"
        fi
    fi
done
exit $exit_status

