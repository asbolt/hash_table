CC = gcc
FLAGS ?= -O2 -mavx2 -pg -I./include 

CSRC = ./source/text_func.c ./source/hash_table_func.c ./source/main.c

.PHONY: all
all: ./build/mymalloc.o ./build/my_hash.o
	$(CC) $(FLAGS) -no-pie -z noexecstack $(CSRC) ./build/my_hash.o ./build/mymalloc.o -o hash_table

./build/mymalloc.o:
	$(CC) -mavx2 -DCOMPILETIME -o ./build/mymalloc.o -c ./source/mymalloc.c

./build/my_hash.o:
	nasm -felf64 ./source/my_hash.asm -o ./build/my_hash.o

.PHONY: clean
clean:
	rm -r ./build/*.o
	rm -r hash_table