#!/bin/sh
#need to compile the program
g++ -Wall -Werror -ansi -pedantic ../src/main.cpp -o rshell

#define some variables to run
test1="echo begin test"
test2="echo test1 ; ls -a ; mkdir #temp ; ls -a; rm -rf temp"
test5="echo test2 ; #mkdir || echo mkdir failed ; ls -a"
test6="echo test3 ; mkdir && echo #mkdir passed ; ls -a"
test3="echo finished test"
test4="exit"
#time to run tests

{
    echo ${test1}
    echo ${test2}
    echo ${test5}
    echo ${test6}
    echo ${test3}
    echo ${test4}
} | ./rshell

#cleanup files
rm rshell