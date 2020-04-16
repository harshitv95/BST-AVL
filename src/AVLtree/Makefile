CC=g++
CFLAGS=-g
DEPS = AVL.h
OBJ = treetester.o ../BST/BST.o AVL.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

avl: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o avl
