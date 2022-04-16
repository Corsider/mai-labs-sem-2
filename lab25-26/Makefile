CC = gcc
CCFLAGS = -std=c99
SRC = main.c deque.c
OBJ = main.o deque.o

all:
	$(CC) -o main $(OBJ) $(CCFLAGS)

pre:
	$(CC) -c $(SRC)

clean:
	rm -f main $(OBJ)