
SOURCES=$(shell find src -type f -name '*.c')
OBJECTS=$(foreach x, $(basename $(SOURCES)), $(x).o)

all:	Project

Project:	$(OBJECTS)
	gcc -Wall -Wextra -Werror -o a.out $(OBJECTS) -lglut -lGL -lGLU -lm $(shell pkg-config --libs lua5.2)

%.o:	%.c
	gcc -Wall -Wextra -Werror -o $@ -c $< $(shell pkg-config --cflags lua5.2)
