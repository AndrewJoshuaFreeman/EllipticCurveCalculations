Elliptic Curve Calculator (C++)

A simple, educational C++ program for performing elliptic curve arithmetic
over different fields:

- Finite fields F_p
- Real numbers R
- Rational numbers Q

The program supports:
- Adding two elliptic curve points
- Scalar multiplication of a point (doubling, tripling, quadrupling, etc.)

This project is intended for learning, experimentation, and demonstration.
It is NOT intended for cryptographic production use.


------------------------------------------------------------
FEATURES
------------------------------------------------------------

- Supports short Weierstrass curves

  Over F_p:
    y^2 ≡ x^3 + a x + b (mod p)

  Over R or Q:
    y^2 = x^3 + a x + b

- Point addition: P + Q
- Scalar multiplication: n * P using double-and-add
- Modular arithmetic with modular inverses
- Exact rational arithmetic with fraction reduction
- Floating-point arithmetic over R with tolerance checks
- Clean separation into logical source files


------------------------------------------------------------
FILE STRUCTURE
------------------------------------------------------------

.
├── main.cpp
├── math.h
├── math.cpp
├── ellipticCurveCalculations.h
├── ellipticCurveCalculations.cpp
├── Makefile
└── README.txt


------------------------------------------------------------
BUILD INSTRUCTIONS
------------------------------------------------------------

Requirements:
- C++17 compatible compiler (e.g. g++)

Build:
  make

Executable produced:
  eccalc

Clean build artifacts:
  make clean


------------------------------------------------------------
RUNNING THE PROGRAM
------------------------------------------------------------

Run:
  ./eccalc

The program will prompt you to:

1. Choose a field:
   1 = Finite field F_p
   2 = Real numbers R
   3 = Rational numbers Q

2. Enter curve parameters a and b

3. Choose an operation:
   1 = Add two points (P + Q)
   2 = Scalar multiplication (n * P)

4. Enter points or scalars as requested


------------------------------------------------------------
INPUT FORMATS
------------------------------------------------------------

Points:
- Enter as: x y
- Point at infinity:
  O

Rational numbers (Q):
- Integer:
  5
- Fraction:
  -3/7

Scalar multiplication:
- Any integer n
  2 = doubling
  3 = tripling
  4 = quadrupling
- Negative values are supported


------------------------------------------------------------
EXAMPLE (FINITE FIELD)
------------------------------------------------------------

Curve:
  y^2 = x^3 + 2x + 2 (mod 17)

Input:
  Field: 1
  p = 17
  a = 2
  b = 2
  Operation: Add two points
  P = (5, 1)
  Q = (6, 3)

Output:
  P + Q = (10, 6)


------------------------------------------------------------
MATHEMATICAL NOTES
------------------------------------------------------------

- Points are checked for curve membership; warnings are shown if invalid.
- Modular inverses use the extended Euclidean algorithm.
- Rational arithmetic is exact and always reduced.
- Floating-point comparisons use a small tolerance.


------------------------------------------------------------
LIMITATIONS
------------------------------------------------------------

- Finite field mode assumes p is prime.
- Not optimized for large cryptographic parameters.
- Intended for educational and experimental use only.


------------------------------------------------------------
LICENSE
------------------------------------------------------------

MIT License.


------------------------------------------------------------
POSSIBLE EXTENSIONS
------------------------------------------------------------

- Compressed point input
- Additional curve forms
- File-based input/output
- Unit tests
- Visualization for curves over R
- Support for standardized cryptographic curves


Happy hacking.
