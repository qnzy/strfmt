CC = gcc
CFLAGS = -Og -Wall -Werror -Wextra -pedantic
test: CFLAGS += -fsanitize=address
coverage: CFLAGS += -fprofile-arcs -ftest-coverage -fPIC
SRC = test.c
HEADER = strfmt.h

bin = testexe

test: $(bin)
	./$(bin)

std: clean
	$(CC) $(CFLAGS) -std=c89 test.c -o $(bin)
	$(CC) $(CFLAGS) -std=c99 test.c -o $(bin)
	$(CC) $(CFLAGS) -std=c11 test.c -o $(bin)

$(bin): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(bin)

clean:
	rm -f *.o
	rm -f $(bin)
	rm -f *.gcda *.gcno *.gcov *.html

lint:
	clang-tidy -checks="*,-llvm-header-guard" -header-filter=".*" *.c

coverage: clean test
	gcovr -r . --html --html-details -o coverage.html

size: clean $(bin)
	nm test -S --size-sort -td

.PHONY: clean all lint coverage size std
