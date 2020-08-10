CC = gcc
CFLAGS = -Og -Wall -Werror -Wextra -pedantic -fsanitize=address -fprofile-arcs -ftest-coverage -fPIC
OBJ = test.o
HEADER = strfmt.h

TESTEXE = test

all: test

$(TESTEXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(TESTEXE) $(OBJ)
	./$(TESTEXE)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f $(TESTEXE)
	rm -f *.gcda *.gcno *.gcov *.html

lint:
	clang-tidy -checks="*,-llvm-header-guard" -header-filter=".*" *.c

coverage: $(TESTEXE)
	gcovr -r . --html --html-details -o coverage.html

.PHONY: clean all lint
