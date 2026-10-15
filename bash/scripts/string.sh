#!/bin/bash
# ==========单双引号的使用
echo 'user: $JAVA_HOME'
echo "user: $JAVA_HOME"

# $ ./string.sh
# user: $JAVA_HOME
# user: D:\Program Files\Java\jdk1.8.0_202

# ==========变量拼接
a="hello"
b="world"
# echo "$a $b" 使用下方方式避免歧义，下划线的连接会使变量名被误导
echo "${a}_${b}"

# hello_world

# ==========子串查询
s="hello bash"
echo ${#s}          # 10（长度）
echo ${s:0:5}       # hello（从 0 取 5 个）
echo ${s:6}         # bash（从 6 到末尾）
echo ${s: -5}       # bash（倒数五个，负数前必须有空格）

# 10
# hello
# bash
# bash

# ==========子串替换
s="foo bar baz bar"
echo ${s/bar/xxx}        # foo xxx baz bar（替换首个）
echo ${s//bar/xxx}       # foo xxx baz xxx（替换所有）
echo ${s/#foo/start}     # start bar baz bar（匹配开头）
echo ${s/%bar/end}       # foo bar baz end（匹配结尾）

# ==========子串删除
s="foo.tar.gz"
echo ${s%.*}         # foo.tar（删除最短后缀）
echo ${s%%.*}        # foo（删除最长后缀）
echo ${s#*.}         # tar.gz（删除最短前缀）
echo ${s##*.}        # gz（删除最长前缀）

# ==========子串判断，注意空格
s="hello"
[[ -z $s ]] && echo "空"
[[ -n $s ]] && echo "非空"
[[ $s == "hello" ]] && echo "相等"
[[ $s != "world" ]] && echo "不等"
[[ $s =~ ^h.*o$ ]] && echo "正则匹配"

# 非空
# 相等
# 不等
# 正则匹配
