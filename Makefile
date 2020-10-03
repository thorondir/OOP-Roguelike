BINNAME=roguelike

CC=g++
CFLAGS=-I. -std=c++11

SRCDIR=./src

LIBS=-lncurses

DEPS = roguelike.h entity.h player.h item.h level.h environment.h renderer.h rng.h
SRC = roguelike.cpp entity.cpp player.cpp item.cpp level.cpp environment.cpp renderer.cpp rng.cpp
OBJ = roguelike.o entity.o player.o item.o level.o environment.o renderer.o rng.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

cursestest: cursestest.cpp
	$(CC) cursestest.cpp -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o $(BINNAME)
