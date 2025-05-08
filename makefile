CC = g++
FLAGS ?= -I./include

CSRC = text_func.cpp hash_table_func.cpp main.cpp 
COBJ = $(CSRC:%.cpp=./build/%.o)

.PHONY: all
all: $(COBJ)
	$(CC) $(FLAGS) $(COBJ) -o hash_table

./build/%.o: source/%.cpp
	$(CC) $(FLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -r ./build/*.o
	rm -r hash_table