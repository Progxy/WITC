C-FLAGS = -std=gnu11 -Wall -Wextra -pedantic

all: witc_test test.bin

witc_test: witc_test.c witc.h utils.h
	gcc -ggdb $(C-FLAGS) $< -o $@

test.bin: test.asm
	fasm $< $@

test: witc_test test.bin
	./witc_test test.bin

# TODO: Add valgrind flags
# VALGRIND-FLAGS = 
mem-test: witc_test test.bin
	valgrind ./witc_test test.bin

clean: witc_test test.bin
	rm -rf witc_test test.bin

