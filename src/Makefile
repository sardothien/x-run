PROGRAM   = x-run
CC        = gcc
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut -lm

$(PROGRAM): main.o scene.o
	$(CC) -o $(PROGRAM) main.o scene.o $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
