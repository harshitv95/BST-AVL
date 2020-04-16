CC=g++ -g
CFLAGS=
DEPS = BST.h
OBJ = treetester.o BST.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bst: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o bst