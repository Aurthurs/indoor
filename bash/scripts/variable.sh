#!/bin/bash
declare -i count=3
echo "count: $count"

# $ ./variable.sh
# count: 3

# ==========
name="world"
echo $name
echo ${name}

echo "${name}.txt"  # 双引号内展开变量
echo '${name}.txt'  # 单引号原样输出

# $ ./variable.sh
# world
# world
# world.txt
# ${name}.txt

# ==========
echo $0     # 脚本名
echo $1     # 第一个参数
echo $#     # 参数个数
echo $@     # 所有参数（每个独立）
echo $*     # 所有参数（合并为一个字符串）
echo $?     # 上一条命令退出码
echo $$     # 当前 shell PID

# $ ./variable.sh 1 2 3
# ./variable.sh
# 1
# 3
# 1 2 3
# 1 2 3
# 0
# 998

# ==========
now=$(date)
echo $now

# Mon, Jul 6, 2026 5:15:57 PM

# ==========
set -euo pipefail
echo ${undefined:-"默认值"}
echo ${undefined2}

# $ ./variable.sh
# 默认值
# ./variable.sh: line 23: undefined2: unbound variable
