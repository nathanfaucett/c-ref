CC := clang

OPT_LVL := -O2

DEPS = ./deps

C_FLAGS := -ansi -pthread $(OPT_LVL) -I$(DEPS) -Wall


all: install build_test run_test

run_test:
	./test/main

build_test: build_lib.o build_thread.o
	$(CC) $(C_FLAGS) ./test/thread.o ./test/lib.o ./test/main.c -o ./test/main

build_lib.o:
	$(CC) $(C_FLAGS) -c ./src/lib.c -o ./test/lib.o

build_thread.o:
	$(CC) $(C_FLAGS) -c ./deps/thread/lib.c -o ./test/thread.o

install:
	clib install

clean:
	$(RM) ./test/main **/*.o **/*~
	$(RM) -rf deps
