BINNAME=roguelike

CC=clang++
CFLAGS=-I. -std=c++11 -Wall -ggdb

SRCDIR=./src

LIBS=-lncurses

DEPS = roguelike.h entity.h player.h item.h level.h environment.h renderer.h rng.h spiralpath.h logger.h input.h enemy.h menu.h inventory.h
SRC = roguelike.cpp entity.cpp player.cpp item.cpp level.cpp environment.cpp renderer.cpp rng.cpp spiralpath.cpp logger.cpp input.cpp enemy.cpp menu.cpp inventory.cpp
OBJ = roguelike.o entity.o player.o item.o level.o environment.o renderer.o rng.o spiralpath.o logger.o input.o enemy.o menu.o inventory.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean testcompile

testcompile: tests.cpp $(filter-out roguelike.o, $(OBJ))
	$(CC) -o tests $^ $(CFLAGS) $(LIBS)

tests: testcompile roguelike
	./tests

clean:
	rm -f *.o $(BINNAME) tests
