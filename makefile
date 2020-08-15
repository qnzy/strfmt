CC = gcc
CFLAGS = -Og -Wall -Werror -Wextra -pedantic
test: CFLAGS += -fsanitize=address
coverage: CFLAGS += -fprofile-arcs -ftest-coverage -fPIC
OBJ = test.o
HEADER = strfmt.h

bin = testexe

test: $(bin)
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

coverage: clean test
	gcovr -r . --html --html-details -o coverage.html

size: clean $(bin)
	nm test -S --size-sort -td

.PHONY: clean all lint coverage size
