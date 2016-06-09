#!/bin/sh
#need to compile the program
g++ -Wall -Werror -ansi -pedantic ../src/main.cpp -o rshell

#define some variables to run
test1="cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2"
test2="ls | sort -r"
test3="ls -a"
test4="echo finished test"
test6="exit"
#time to run tests

{
    echo ${test1}
    echo ${test2}
    echo ${test3}
    echo ${test4}
    echo ${test6}
} | ./rshell

#cleanup files
rm rshell