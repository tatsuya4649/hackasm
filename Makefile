
CC := gcc
CFLAGS := -g -Wall -Wextra
INCLUDE := -I./include

main:	./src/main.c
	gcc -o ./bin/main $(INCLUDE) ./src/main.c ./src/parser.c
