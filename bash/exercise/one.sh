#!/bin/bash
# 接收脚本参数 首都 '(1,2,3,4)'，判断非空。循环打印第二个参数括号里的元素

set -euo pipefail

# 所有参数都是作为字符串类型接收
param1=$1
raw=$2

# 去掉括号，按逗号拆成数组
raw=${raw#\(}
raw=${raw%\)}

# 把 $raw 的内容临时按逗号切分，分别存入 param2[0]、param2[1]
IFS=',' read -ra param2 <<< "${raw}"

echo "${param1}"

printf '%s\n' "${param2[@]}"

# ./exercise/one.sh 首都 '(1,2,3,4)'
# 首都
# 1
# 2
# 3
# 4
