CC=g++
CC_FLAGS= -Wall -Werror -ansi -pedantic
EXEC=rshell
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
OBJDIR=obj

$(EXEC): $(OBJECTS)
	mkdir -p bin
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
	rm -rf bin