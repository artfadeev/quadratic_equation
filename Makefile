.PHONY: build check format docs clean precommit
FLAGS = -Wall -Wextra -pedantic
RELEASE_FLAGS = $(FLAGS) -O3 -DNDEBUG 
TEST_FLAGS = $(FLAGS) -g

build:
	$(CC) $(RELEASE_FLAGS) -c quadratic_equation.c -lm
	ar rcs libquadratic_equation.a quadratic_equation.o

check:
	$(CC) $(TEST_FLAGS) -o tests/test tests/test.c quadratic_equation.c -lm
	./tests/test

example: build
	$(CC) $(TEST_FLAGS) -o examples/cli examples/cli.c libquadratic_equation.a -lm

format:
	clang-format -i *.c *.h tests/*.c examples/*.c

docs:
	doxygen Doxyfile

clean:
	-rm -rf html/ man/ # doxygen-generated docs 
	-rm tests/test
	-rm examples/cli
	-rm *.o *.a # build files

precommit:
	make format
	make check
	make clean
	make docs
	@echo "Ready"

