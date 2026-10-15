#!/bin/bash
# ==========批量创建文件
mkdir -p ./files ./fileChange
for i in {1..3}; do
    touch ./files/file${i}.txt
done

# ==========批量重命名文件
num=$(ls ./files/*.txt | wc -l)
for ((i=1; i<=num; i++)); do
    mv -v ./files/file${i}.txt ./fileChange/file${i}.png
done
