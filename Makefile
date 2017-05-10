CFLAG = -std=c++11 -Wall -Werror -ansi -pedantic
CC = g++

all :
	mkdir -p bin
	$(CC) $(CFLAG) src/main.cpp src/Command.cpp \
	src/Executable.cpp src/Connector.cpp \
	-I include -o bin/rshell
clean :
	rm -rf bin
