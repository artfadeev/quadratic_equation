# [`quadratic_equation`](https://github.com/artfadeev/quadratic_equation)
**This is a test task for an internship. You shouldn't use this code.**

This C library consists of a single function which finds real roots of quadratic equations with real coefficients.

## Build & Usage
Use `make build` (POSIX system and C99 or later are required) to build `quadratic_equation` as a static library (`libquadratic_equation.a`). Include `quadratic_equation.h` header to use it. The only dependency is libm, link it to use this library. 

`examples/cli.c` contains an example of usage, `make example` recipe contains corresponding build flags.

## Development
Run `make check` to compile and run tests. Use `clang-format` via `make format` to format source code.
Use `make precommit` to ensure that tests pass, code is formatted and documentation is up-to-date.

## Documentation
Run `make docs` (you'll need [doxygen](https://www.doxygen.nl/index.html) installed for this) to produce docs in html and manpage formats.
