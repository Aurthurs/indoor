#!/bin/bash
# ==========定义
arr=(a b c)             # 定义
arr[3]=d                # 单独赋值（索引可不连续）
arr+=(e)                # 追加

# ==========长度
echo ${arr[0]}          # a
echo ${arr[@]}          # a b c d e（所有元素）
echo ${#arr[@]}         # 5（长度）
echo ${!arr[@]}         # 0 1 2 3 4（所有索引）

unset arr[1]            # 删除索引为1的元素
echo ${arr[@]}         # a c d e（删除后）

# ==========关联数组（类似字典）
declare -A map
map["key"]="value"
echo ${map["key"]}
echo ${!map[@]}
echo ${map[@]}
