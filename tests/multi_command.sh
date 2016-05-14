#!/bin/sh
#need to compile the program
g++ -Wall -Werror -ansi -pedantic ../src/main.cpp -o rshell

#define some variables to run
test1="echo begin test"
test2="ls -a ; mkdir temp ; ls -a; rm -rf temp"
test5="mkdir || echo mkdir failed ; ls -a"
test6="mkdir && echo mkdir passed ; ls -a"
test7="||"
test3="echo finished test"
test4="exit"
newline="echo"
#time to run tests

{
    echo ${test1}
    echo ${newline}
    echo ${test2}
    echo ${newline}    
    echo ${test5}
    echo ${newline}    
    echo ${test6}
    echo ${newline}    
    echo ${test7}
    echo ${newline}    
    echo ${test3}
    echo ${newline}    
    echo ${test4}
} | ./rshell

#cleanup files
rm rshell