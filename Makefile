
SOURCES=$(shell find src -type f -name '*.c')
OBJECTS=$(foreach x, $(basename $(SOURCES)), $(x).o)

CFLAGS=-Wall -Wextra -Werror
LIBFLAGS=-lglut -lGL -lGLU -lm $(shell pkg-config --cflags --libs lua5.2)

all:	Project

clean:
	find src -type f -name '*.o' | xargs rm
	rm a.out

debug:	CFLAGS += -g
debug:	Project

Project:	$(OBJECTS)
	gcc $(CFLAGS) -o a.out $(OBJECTS) $(LIBFLAGS)

%.o:	%.c
	gcc $(CFLAGS) -o $@ -c $< $(LIBFLAGS)
