#!/bin/bash

clear
echo "###################################################################"
echo "#           LEAKS TESTS CASES FOR PROJECT S21_SMART_CALC          #"
echo "###################################################################"
echo
GCC=$1
FLAGS=$(echo $2)
LIBS_OS_CHECK=$(echo $3)
FLAG_GCOV=$4
OSLINUX=$(echo $5)

cd test
find . -name "*.check" | while read FILE
do
    echo "--------------------------------------------"
    filename=$(basename "$FILE" \.check)
    checkmk $filename.check > test_$filename.c
    $GCC $FLAGS $FLAG_GCOV -c test_$filename.c s21*.c
    $GCC $FLAGS $FLAG_GCOV -o test_$filename test_$filename.o s21*.c $LIBS_OS_CHECK
    echo "TESTS CASES --> $filename:"
    ./test_$filename

    if [[ $OSLINUX -eq 1 ]]
        then
            ./linux_leak.sh "test_$filename"
        else
            ./mac_leak.sh "test_$filename"
    fi
    echo
    rm -f test_$filename
done
