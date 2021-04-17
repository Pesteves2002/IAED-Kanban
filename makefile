CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g
proj1: *.c 
proj1.zip: *.c 
	zip proj1.zip *.c 
clean::
	rm -f proj1 a.out *.o core tests/*.diff proj1.zip