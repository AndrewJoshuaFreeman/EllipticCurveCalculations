#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cstdint>
#include <string>
#include <stdexcept>

enum class FieldType {
    FINITE_FP,
    REALS,
    RATIONALS
};

struct Rational {
    int64_t num{0};
    int64_t den{1}; // always > 0

    Rational() = default;
    Rational(int64_t n) : num(n), den(1) {}
    Rational(int64_t n, int64_t d);

    static int64_t gcd(int64_t a, int64_t b);
    void normalize();

    std::string toString() const;
};

Rational operator+(const Rational& a, const Rational& b);
Rational operator-(const Rational& a, const Rational& b);
Rational operator*(const Rational& a, const Rational& b);
Rational operator/(const Rational& a, const Rational& b);
bool operator==(const Rational& a, const Rational& b);

int64_t mod_norm(int64_t x, int64_t p);
int64_t mod_add(int64_t a, int64_t b, int64_t p);
int64_t mod_sub(int64_t a, int64_t b, int64_t p);
int64_t mod_mul(int64_t a, int64_t b, int64_t p);

// modulor inverse (throws if no inv)
int64_t mod_inv(int64_t a, int64_t p);

#endif

