CC:=gcc
CFLAGS:=-lglut -lGL \
	-v
PROJECT:=hellotriangle

default:
	$(CC) $(CFLAGS) -Wall -o app $(PROJECT)/main.c

test: default
	./app

clean:
	rm app
