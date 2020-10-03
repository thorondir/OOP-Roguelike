BINNAME=roguelike

CC=g++
CFLAGS=-I.

SRCDIR=./src

LIBS=-lncurses

SRC = roguelike.cpp entity.cpp player.cpp item.cpp level.cpp environment.cpp renderer.cpp
OBJ = roguelike.o entity.o player.o item.o level.o environment.o renderer.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

cursestest: cursestest.cpp
	$(CC) cursestest.cpp -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o $(BINNAME)
