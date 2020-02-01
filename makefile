CC = gcc
CFLAGS = -Og
OBJ = test.o
HEADER = strfmt.h

TESTEXE = test

all: test

$(TESTEXE): $(OBJ)
	$(CC) -o $(TESTEXE) $(OBJ)
	./$(TESTEXE)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f $(TESTEXE)

.PHONY: clean all
