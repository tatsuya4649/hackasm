
CC := gcc
CFLAGS := -g -Wall -Wextra -O0
INCLUDE := -I./include
ISRC := -I./src
SRC := ./src/
BIN := ./bin/
MAIN = $(SRC)main.c
PARSER = $(SRC)parser.c
CODE = $(SRC)code.c
MAINBI = $(BIN)main
SYM = $(SRC)sym.c

RSRC := $(SRC)parser.c $(SRC)main.c $(SRC)code.c $(SRC)sym.c

all:	$(MAIN) $(PARSER) $(SYM) $(CODE)
	gcc $(CFLAGS) -o $(BIN)main $(INCLUDE) $^

$(BIN)%.o:	$(SRC)%.c
	gcc -c -o $@ $< $(INCLUDE) $(ISRC)

run:
	$(MAINBI) ./test/$(FILE).asm
test_run: all
	$(MAINBI) ./test/test.asm
clean:
	rm -rf $(BIN)*
