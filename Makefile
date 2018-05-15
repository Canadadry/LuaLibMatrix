CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LIBFLAG= -fpic -dynamiclib -Wl,-undefined,dynamic_lookup

all: run_exe run_lib

dir: 
	mkdir -p build

lua_matrix.so: build/lua_matrix.o build/matrix.o
	@$(CC) -o build/lua_matrix.so  $(LIBFLAG) build/matrix.o build/lua_matrix.o $(LDFLAGS)

run_exe: test
	./build/test

run_lib: lua_matrix.so
	lua test/main.lua

test: build/test.o build/matrix.o
	@$(CC) -o build/test build/matrix.o build/test.o $(LDFLAGS)

matrix: build/matrix.o
	@$(CC) -o build/matrix.so build/matrix.o $(LDFLAGS)

build/lua_matrix.o: src/lua_matrix.c
	@$(CC) -o build/lua_matrix.o -c src/lua_matrix.c $(CFLAGS)

build/matrix.o: src/matrix.c
	@$(CC) -o build/matrix.o -c src/matrix.c $(CFLAGS)

build/test.o: test/main.c
	@$(CC) -o build/test.o -c test/main.c $(CFLAGS)

clean:
	rm -rf build/*

mrproper: clean
	rm -rf /matrix.so