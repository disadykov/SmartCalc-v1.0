#!/bin/bash

FILE_TEST_NAME=$1

testing()
{
    valgrind --log-file="valgrind_test_leaks.log" --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$FILE_TEST_NAME > test_leaks.log
    leak=$(grep ERROR valgrind_test_leaks.log)

    if [[ $leak == *"0 errors from 0 contexts"* ]]
    then
        echo "###################################################"
        echo "VALGRIND --> SUCCESS: Leaks not found!"
        echo "###################################################"
    else
        echo "###################################################"
        echo "VALGRIND --> FAIL: Leaks found!"
        echo "###################################################"
    fi
    rm test_leaks.log
    rm valgrind_test_leaks.log
}

testing
