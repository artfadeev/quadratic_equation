#include "../quadratic_equation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: ./cli a b c");
    return EXIT_FAILURE;
  };
  double a = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double c = strtod(argv[3], NULL);

  printf("Solving %gx^2 + %gx + %g = 0\n", a, b, c);
  double x0, x1;

  switch (solve_equation(a, b, c, &x0, &x1)) {
  case QUADRATIC_EQUATION_INFINITE_ROOTS:
    printf("All real numbers are roots\n");
    break;
  case QUADRATIC_EQUATION_NO_ROOTS:
    printf("No roots\n");
    break;
  case QUADRATIC_EQUATION_LINEAR:
    printf("Linear equation, one root: %g\n", x0);
    break;
  case QUADRATIC_EQUATION_COMPLEX_ROOTS:
    printf("Quadratic equation, two complex roots.\n");
    break;
  case QUADRATIC_EQUATION_REAL_ROOTS:
    printf("Quadratic equation, roots %g and %g\n", x0, x1);
    break;
  }
}
