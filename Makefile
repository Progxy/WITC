C-FLAGS = -std=c11 -Wall -Wextra -pedantic

witc: witc.c utils.h
	gcc -ggdb $(C-FLAGS) $< -o $@

clean: witc
	rm -rf witc

