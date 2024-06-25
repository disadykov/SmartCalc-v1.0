#!/bin/bash

FILE_TEST_NAME=$1

testing()
{
    leaks -atExit -- ./$FILE_TEST_NAME > test_leaks.log
    leak=$(grep -A100000 leaks test_leaks.log)
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
    then
        echo "###################################################"
        echo "LEAKS --> SUCCESS: Leaks not found!"
        echo "###################################################"
    else
        echo "###################################################"
        echo "LEAKS --> FAIL: Leaks found!"
        echo "###################################################"
    fi
    rm test_leaks.log
}

testing
