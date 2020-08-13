CC = gcc
CFLAGS = -Og -Wall -Werror -Wextra -pedantic -fsanitize=address
coverage: CFLAGS = -Og -Wall -Werror -Wextra -pedantic -fsanitize=address -fprofile-arcs -ftest-coverage -fPIC
size: CFLAGS = -Og -Wall -Werror -Wextra -pedantic
OBJ = test.o
HEADER = strfmt.h

bin = test

doTest: $(bin)
	./$(bin)

$(bin): $(OBJ)
	$(CC) $(CFLAGS) -o $(bin) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f $(bin)
	rm -f *.gcda *.gcno *.gcov *.html

lint:
	clang-tidy -checks="*,-llvm-header-guard" -header-filter=".*" *.c

coverage: doTest
	gcovr -r . --html --html-details -o coverage.html

size: $(bin)
	nm test -S --size-sort -td

.PHONY: clean all lint
