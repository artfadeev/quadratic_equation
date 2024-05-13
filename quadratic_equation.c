#include "quadratic_equation.h"
#include <assert.h>
#include <math.h>

quadratic_equation_rc solve_equation(double a, double b, double c,
                                     double x0[static 1], double x1[static 1]) {
  // out-parameters must be provided
  assert(x0);
  assert(x1);
  // this function doesn't handle NANs, infinities, etc
  assert(!isnan(a));
  assert(!isnan(b));
  assert(!isnan(c));

  // corner case: constant polynomial
  if (a == 0 && b == 0) {
    *x0 = *x1 = NAN;
    return c == 0 ? QUADRATIC_EQUATION_INFINITE_ROOTS
                  : QUADRATIC_EQUATION_NO_ROOTS;
  }

  // corner case: linear polynomial
  if (a == 0) {
    *x0 = -c / b;
    *x1 = NAN;
    return QUADRATIC_EQUATION_LINEAR;
  }

  // quadratic equation solution using discriminant
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    *x0 = *x1 = NAN;
    return QUADRATIC_EQUATION_COMPLEX_ROOTS;
  }

  *x0 = (-b - sqrt(discriminant)) / (2 * a);
  *x1 = (-b + sqrt(discriminant)) / (2 * a);

  return QUADRATIC_EQUATION_REAL_ROOTS;
}
