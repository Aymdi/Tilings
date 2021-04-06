CFLAGS=-std=c99 -Wall -Wextra -g
CC=gcc

SRC=$(wildcard src/*.c)
OBJ=$(SRC:%.c=%.o)

TSRC=$(wildcard tst/*.c)
TOBJ=$(TSRC:%.c=%.o)

all: project

%.o: %.c

project: $(OBJ)
	$(CC) src/*.o -o project

src/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

test: $(SRC) $(TSRC)
	$(CC) $(CFLAGS) src/color.c src/tile.c src/file.c src/game.c src/pattern.c tst/test_main.c -o test && ./test

clean:
	rm -rf project test src/*.o tst/*.o
