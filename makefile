CC = gcc
CCFLAGS = -Og
OBJ = test.o strfmt.o

TESTEXE = test

all: test

$(TESTEXE): $(OBJ)
	$(CC) -o $(TESTEXE) $(OBJ)
	./$(TESTEXE)

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f $(TESTEXE)

.PHONY: clean all
