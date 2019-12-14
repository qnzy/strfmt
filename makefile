CC = gcc
OBJ = test.o strfmt.o

all: test

test: $(OBJ)
	$(CC) -o test $(OBJ)
	./test

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f test

.PHONY: clean all
