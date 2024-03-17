test_dir=../hidden_set
output_dir=../test/ir_test/output
cd ../../bin
for file in $test_dir/*; do
    if [ -f "$file" ]; then
        if [ "${file##*.}" = "pas" ]; then
            ./pascc -i "$file" -o "$output_dir/$(basename "$file").c"
        fi
    fi
done