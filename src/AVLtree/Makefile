CC=g++ -g
CFLAGS=
DEPS = ../BST/BST.h AVL.h
OBJ = treetester.o ../BST/BST.o AVL.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bst: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o bst