#!/bin/bash
# ===========条件判断
if [[ $1 -ge 90 ]]; then
    echo "优秀"
elif [[ $1 -gt 60 ]]; then
    echo "及格"
else
    echo "不及格"
fi

# ===========case
ext=${2#*.}
echo "文件扩展名：${ext}"
case ${ext} in
    txt)
        echo "文本文件";;
    *)
        echo "其他文件";;
esac

# $ ./scripts/condition.sh 55 123.txt
# 不及格
# 文件扩展名：txt
# 文本文件
