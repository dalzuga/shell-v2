all:
	gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
g:
	gcc -g -Wall -Werror -Wextra -pedantic *.c -o hsh
g3:
	gcc -g3 -Wall -Werror -Wextra -pedantic *.c -o hsh
run:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./hsh
clean:
	rm -f hsh
