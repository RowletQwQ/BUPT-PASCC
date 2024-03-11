# 进入到根目录的 build 文件夹
cd ../../build

# 执行 make
make

# 进入到 bin 文件夹
cd ../bin

# 测试集目录
test_dir="../open_set"

# 逐个处理测试集的所有文件
for file in "$test_dir"/*; do
    if [ -f "$file" ]; then
        # 如果是 .pas 文件，则进行编译
        if [ "${file##*.}" = "pas" ]; then
            ./pascc -i $file > ../test/ir_test/output/$(basename "$file").ir
        fi
    fi
done

