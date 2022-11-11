CC = gcc
CFLAGS = -Og -Wall -Werror -Wextra -pedantic 
CFLAGS += -Wno-format # allow bad calls in the test file
test: CFLAGS += -fsanitize=address 
coverage: CFLAGS += -fprofile-arcs -ftest-coverage -fPIC
SRC = test.c
HEADER = strfmt.h

bin = testexe

test: $(bin)
	./$(bin)

std: clean
	$(CC) $(CFLAGS) -std=c89 $(SRC) -o $(bin)
	$(CC) $(CFLAGS) -std=c99 $(SRC) -o $(bin)
	$(CC) $(CFLAGS) -std=c11 $(SRC) -o $(bin)

$(bin): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) -o $(bin)

clean:
	rm -f *.o
	rm -f $(bin)
	rm -f *.gcda *.gcno *.gcov *.html

lint:
	clang-tidy -checks="*,-llvm-header-guard,-altera*,-clang-diagnostic-format,-readability-function-cognitive-complexity,-llvmlibc*" -header-filter=".*" *.c

coverage: clean test
	gcovr -r . --html --html-details -o coverage.html

size: clean $(bin)
	nm $(bin) -S --size-sort -td

.PHONY: clean all lint coverage size std
