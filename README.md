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
MATHEMATICAL BACKGROUND
------------------------------------------------------------

This program works with elliptic curves in short Weierstrass form:

  y^2 = x^3 + a x + b

Depending on the selected field, all arithmetic is performed over:

- A finite field F_p (integers modulo a prime p)
- The rational numbers Q
- The real numbers R

Only non-singular curves are assumed (i.e., curves for which the
discriminant is nonzero).


Elliptic Curve Group Law
-----------------------

The set of points on an elliptic curve, together with a special point
called the point at infinity O, forms an abelian group.

Group elements:
- All points (x, y) satisfying the curve equation
- The point at infinity O, which acts as the identity

Identity:
  P + O = P

Inverse:
  If P = (x, y), then -P = (x, -y)
  (negation is performed modulo p in F_p)


Point Addition (P + Q)
---------------------

For two distinct points P = (x1, y1) and Q = (x2, y2) with x1 != x2:

1. Compute the slope:
     λ = (y2 - y1) / (x2 - x1)

2. Compute the resulting point:
     x3 = λ^2 - x1 - x2
     y3 = λ(x1 - x3) - y1

The result R = (x3, y3) is the sum P + Q.

If x1 = x2 and y1 = -y2, then:
  P + Q = O


Point Doubling (P + P)
---------------------

When adding a point to itself, the tangent line at P is used.

For P = (x, y) with y != 0:

1. Compute the slope:
     λ = (3x^2 + a) / (2y)

2. Compute:
     x3 = λ^2 - 2x
     y3 = λ(x - x3) - y

If y = 0, the tangent is vertical and:
  P + P = O


Scalar Multiplication (n · P)
-----------------------------

Scalar multiplication is defined as repeated addition:

  n · P = P + P + ... + P  (n times)

This program computes n · P using the double-and-add algorithm:

- Express n in binary
- Repeatedly double the current point
- Add to the result when the corresponding bit is set

This runs in O(log n) point operations.


Field-Specific Notes
--------------------

Finite Field F_p:
- All arithmetic is performed modulo p
- Division is implemented using modular inverses
- The inverse of a modulo p exists if gcd(a, p) = 1

Rational Numbers Q:
- All values are stored as reduced fractions
- Arithmetic is exact (no rounding error)

Real Numbers R:
- Arithmetic uses double-precision floating point
- Equality checks use a small tolerance to account for rounding error


Point at Infinity
-----------------

The point at infinity O is treated as a special value and represents
the identity element of the group. It is returned in cases such as:

- Adding a point to its inverse
- Doubling a point with y = 0
- Multiplying a point by 0

