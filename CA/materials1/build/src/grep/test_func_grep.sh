#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s test_0_grep.txt"
"for s21_grep.c s21_grep.h Makefile"
"for s21_grep.c"
"-e for -e ^int s21_grep.c s21_grep.h Makefile"
"-e for -e ^int s21_grep.c"
"-e regex -e ^print s21_grep.c"
"-e while -e void s21_grep.c Makefile"
)

declare -a extra=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt test_2_grep.txt test_4_grep.txt"
"-n for test_1_grep.txt"
"-n ^\} test_1_grep.txt"
"-n ^\} test_1_grep.txt test_4_grep.txt"
"-c ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-n = test_2_grep.txt"
"-n = test_1_grep.txt test_2_grep.txt"
"-i INT test_5_grep.txt"
"-i INT test_5_grep.txt test_1_grep.txt"
"-e test_1_grep.txt test_2_grep.txt"
"-i int test_5_grep.txt"
"-i int test_5_grep.txt test_2_grep.txt"
"-c aboba test_1_grep.txt test_5_grep.txt"
"-c aboba test_5_grep.txt"
"-v y test_1_grep.txt"
"-v y test_1_grep.txt test_1_grep.txt"
"-n ) test_5_grep.txt"
"-n ) test_5_grep.txt test_2_grep.txt"
"-l for test_1_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-o int test_4_grep.txt"
"-o int test_4_grep.txt test_5_grep.txt"
"-e = -e out test_5_grep.txt"
"-e = -e out test_5_grep.txt test_1_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt"
"-e ing -e as -e the -e not -e is test_6_grep.txt test_2_grep.txt"
"-c . test_1_grep.txt"
"-c . test_1_grep.txt test_3_grep.txt"
"-l for no_file.txt test_2_grep.txt"
"-f test_3_grep.txt test_5_grep.txt"
"-f test_3_grep.txt test_5_grep.txt test_6_grep.txt"
"-e = -e test_5_grep.txt test_1_grep.txt"
"-h for test_1_grep.txt"
"-h for test_1_grep.txt test_2_grep.txt"
"-s king test_6_grep.txt"
"-s for test_1_grep.txt test_2_grep.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in e i v c l n h s o f
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done



echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
