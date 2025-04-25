C-FLAGS = -std=c11 -Wall -Wextra -pedantic

witc_test: witc_test.c witc.h utils.h
	gcc -ggdb $(C-FLAGS) $< -o $@

clean: witc_test
	rm -rf witc_test

