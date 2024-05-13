#include "../quadratic_equation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

#define EPS (1e-9)
#define GRID_SIZE (125 * 4) // keep it multiple of 4

#define run_test(test_function)                                                \
  {                                                                            \
    printf("running " #test_function "... ");                                  \
    fflush(stdout);                                                            \
    test_function();                                                           \
    printf(" passed!\n");                                                      \
  }

typedef struct test_case {
  // input
  double a;
  double b;
  double c;

  // expected output
  quadratic_equation_rc rc;
  double x0;
  double x1;
} test_case;

void assert_close(double expected, double result, int line) {
  if (isnan(expected) && !isnan(result)) {
    fprintf(stderr, "assert_close fail at line %d: expected NAN, got %g\n",
            line, result);
    exit(1);
  } else if (!isnan(expected) &&
             (isnan(result) || fabs(expected - result) > EPS)) {
    fprintf(stderr, "assert_close fail at line %d: %g != %g\n", line, expected,
            result);
    exit(1);
  }
}

// Check solve_equation results against precomputed cases
void test_basic(void) {
  test_case tests[] = {
      {1, 2, 1, QUADRATIC_EQUATION_REAL_ROOTS, -1, -1},
      {1, 0, -1, QUADRATIC_EQUATION_REAL_ROOTS, -1, 1},
      {1, 0, -2, QUADRATIC_EQUATION_REAL_ROOTS, -sqrt(2), +sqrt(2)},
      {3, 14, -5, QUADRATIC_EQUATION_REAL_ROOTS, -5, 1. / 3},
      {1, 0, 0, QUADRATIC_EQUATION_REAL_ROOTS, 0, 0},

      // no real roots
      {1, 0, 1, QUADRATIC_EQUATION_COMPLEX_ROOTS, NAN, NAN},
      {1, -2, 2, QUADRATIC_EQUATION_COMPLEX_ROOTS, NAN, NAN},

      // non-quadratic equations
      {0, 1, -5, QUADRATIC_EQUATION_LINEAR, 5, NAN},
      {0, 0, 4, QUADRATIC_EQUATION_NO_ROOTS, NAN, NAN},
      {0, 0, 0, QUADRATIC_EQUATION_INFINITE_ROOTS, NAN, NAN},
  };
  size_t tests_count = sizeof(tests) / sizeof(tests[0]);

  for (size_t i = 0; i < tests_count; i++) {
    double x0, x1;
    quadratic_equation_rc rc =
        solve_equation(tests[i].a, tests[i].b, tests[i].c, &x0, &x1);

    assert(rc == tests[i].rc);
    assert_close(tests[i].x0, x0, __LINE__);
    assert_close(tests[i].x1, x1, __LINE__);
  }
}

// Run solve_equation on large grid of coefficient values
void test_bruteforce(void) {
  assert(GRID_SIZE % 4 == 0);
  size_t quarter_size = GRID_SIZE / 4;

  double grid[GRID_SIZE];
  for (size_t i = 0; i < quarter_size; i++) {
    grid[i] = (double)i;
    grid[i + quarter_size] = -grid[i];
    grid[i + 2 * quarter_size] = 1 / (grid[i] + 1);
    grid[i + 3 * quarter_size] = -1 / (grid[i] + 1);
  }

  for (size_t i = 0; i < GRID_SIZE * GRID_SIZE * GRID_SIZE; i++) {
    double a = grid[i % GRID_SIZE];
    double b = grid[(i / GRID_SIZE) % GRID_SIZE];
    double c = grid[(i / (GRID_SIZE * GRID_SIZE))];

    double x0, x1;
    solve_equation(a, b, c, &x0, &x1);

    if (!isnan(x0))
      assert_close(0, a * x0 * x0 + b * x0 + c, __LINE__);
    if (!isnan(x1))
      assert_close(0, a * x1 * x1 + b * x1 + c, __LINE__);
  }
}

int main() {
  run_test(test_basic);
  run_test(test_bruteforce);
}
