CC:=gcc
CFLAGS:=-v
LIBS:=-lglut -lGLEW -lGL -lGLU -lm
PROJECT:=study

default:
	$(CC) $(CFLAGS) -Wall -o app $(PROJECT)/main.c $(LIBS)

test: default
	./app

clean:
	rm app
