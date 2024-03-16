# 测试目录
test_dir=../open_set

# 输出目录
output_dir=../test/ir_test/output

# 进入到 bin 目录
cd ../../bin

# 执行测试
for file in $test_dir/*; do
    if [ -f $file ]; then
        if [ ${file##*.} = pas ]; then
            echo "Testing $file"
            ./pascc -i $file -d 4 > ../test/ir_test/output/$(basename $file).ir
            echo "Testing $file done"
        fi
    fi
done