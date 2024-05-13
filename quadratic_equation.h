/** \file */

/**
 \mainpage quadratic_equation

 This module provides \ref solve_equation function for solving quadratic
 equations with real coefficients. See \ref quadratic_equation.h for docs.
 */

#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

/** Quadratic equation outcomes
  \li \c QUADRATIC_EQUATION_INFINITE_ROOTS -- corner case, all coefficients are
  equal to zero

  \li \c QUADRATIC_EQUATION_NO_ROOTS -- corner case, only constant
  coefficient is not zero

  \li \c QUADRATIC_EQUATION_LINEAR -- corner case,
  quadratic coefficient is zero, linear coefficient is not zero

  \li \c QUADRATIC_EQUATION_COMPLEX_ROOTS -- equation has two complex roots

  \li \c QUADRATIC_EQUATION_REAL_ROOTS -- equation has two real (possibly equal)
  roots
*/
typedef enum {
  QUADRATIC_EQUATION_INFINITE_ROOTS = -3,
  QUADRATIC_EQUATION_NO_ROOTS = -2,
  QUADRATIC_EQUATION_LINEAR = -1,
  QUADRATIC_EQUATION_COMPLEX_ROOTS = 0,
  QUADRATIC_EQUATION_REAL_ROOTS = 1,
} quadratic_equation_rc;

/** Find real roots of a quadratic equation with real coefficients

 \param a quadratic coefficient
 \param b linear coefficient
 \param c constant coefficient
 \param x0 (out parameter, non-NULL) where to store the smallest root
 \param x1 (out parameter, non-NULL) where to store the largest root

 \return Return code which classifies provided quadratic equation — value of
 \ref quadratic_equation_rc type. \c x0 and \c x1 are populated with root
 values. If there are less than two solutions, remaining values are set to NAN.

 This function doesn't check input values for NANs and infinities.
 This function uses discriminant method, which may make results highly
 imprecise.
*/
quadratic_equation_rc solve_equation(double a, double b, double c,
                                     double x0[static 1], double x1[static 1]);
#endif
