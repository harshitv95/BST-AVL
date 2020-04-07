CC=g++
CFLAGS=-I -g
DEPS = BST.h
OBJ = treetester.o BST.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bst: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)