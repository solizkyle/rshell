#!/bin/sh

STRING="ls ..\necho rshell\nmkdir inputs\necho `pwd`\ncat ../src/Ors.h\nexit"
echo -e $STRING | ../rshell