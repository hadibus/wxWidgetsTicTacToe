CC=g++
OUTPUT=ticTacToe
CFLAGS= -Wall -std=c++14
SOURCES= onInit.cpp
LOADO=` wx-config --cflags --libs`

all: build 

build:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(LOADO)

run: build
	./$(OUTPUT)

clean:
	rm $(OUTPUT)
