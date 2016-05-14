#complier to use
CC=g++
#flags for compiler
CC_FLAGS= -Wall -Werror -ansi -pedantic
#executable filename
EXEC=rshell
OBJECTS=$(SOURCES:.cpp=.o)
#make all will create all necessary files
all: rshell

rshell:
	$(CC) $(CC_FLAGS) -I header -o rshell src/main.cpp
	mkdir -p bin
	mv rshell bin
clean:
	rm -rf bin