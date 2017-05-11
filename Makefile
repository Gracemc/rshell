CFLAG = -std=c++11 -Wall -Werror -pedantic -I include
CC = g++
SOURCE = src/main.cpp src/Command.cpp src/Connector.cpp src/Executable.cpp \
	 src/parse.cpp

all : rshell

rshell :
	mkdir  bin
	$(CC) $(CFLAG) $(SOURCE) -o bin/rshell

.PHONY : clean
clean :
	rm -rf bin
