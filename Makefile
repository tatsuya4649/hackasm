
CC := gcc
CFLAGS := -g -Wall -Wextra
INCLUDE := -I./include
SRC := -I./src
MAIN = ./bin/main.o
PARSER = ./bin/parser.o
CODE = ./bin/code.o

all:	$(MAIN) $(PARSER)
	gcc -o ./bin/main $(INCLUDE) ./src/main.c ./src/parser.c ./src/code.c

$(MAIN):	./src/main.c
	gcc -c -o $(MAIN) ./src/main.c $(INCLUDE)

$(PARSER):	./src/parser.c
	gcc -c -o $(PARSER) ./src/parser.c $(INCLUDE) $(SRC)

$(CODE):	./src/code.c
	gcc -c -o $(CODE) ./src/code.c $(INCLUDE) $(SRC)
