#!/bin/sh
#need to compile the program
g++ -Wall -Werror -ansi -pedantic ../src/main.cpp -o rshell

#define some variables to run
test1="echo begin test"
test2="test -e ../src/main.cpp"
test5="[ -e ../src/main.cpp ]"
test6="test ../bin/randomfile"
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