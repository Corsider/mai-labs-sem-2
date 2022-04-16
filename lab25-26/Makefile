CC = gcc
CCFLAGS = -std=c99
SRC = main.c deque.c
OBJ = main.o deque.o
HD = deque.h

all: $(OBJ)
	$(CC) -o main $(OBJ) $(CCFLAGS)

main.o: $(HD)
	$(CC) $(CCFLAGS) -c main.c

deque.o: $(HD)
	$(CC) $(CCFLAGS) -c deque.c

pre:
	$(CC) -c $(SRC)

clean:
	rm -f main $(OBJ)