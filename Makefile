CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS=

all: dir  run

dir: 
	mkdir -p build

run: test
	./build/test

test: build/test.o build/matrix.o
	@$(CC) -o build/test build/matrix.o build/test.o $(LDFLAGS)

matrix: build/matrix.o
	@$(CC) -o build/matrix.so build/matrix.o $(LDFLAGS)

build/matrix.o: src/matrix.c
	@$(CC) -o build/matrix.o -c src/matrix.c $(CFLAGS)

build/test.o: test/main.c
	@$(CC) -o build/test.o -c test/main.c $(CFLAGS)

clean:
	rm -rf build/*

mrproper: clean
	rm -rf /matrix.so