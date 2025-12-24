#include "math_utils.h"
#include <sstream>
#include <cstdlib>

static int64_t iabs64(int64_t x) { return x < 0 ? -x : x; }

Rational::Rational(int64_t n, int64_t d) : num(n), den(d) {
    if (den == 0) throw std::invalid_argument("Rational denominator cannot be 0");
    normalize();
}

int64_t Rational::gcd(int64_t a, int64_t b) {
    a = iabs64(a);
    b = iabs64(b);
    while (b != 0) {
        int64_t t = a % b;
        a = b;
        b = t;
    }
    return a == 0 ? 1 : a;
}

void Rational::normalize() {
    if (den < 0) { den = -den; num = -num; }
    int64_t g = gcd(num, den);
    num /= g;
    den /= g;
}

std::string Rational::toString() const {
    std::ostringstream oss;
    if (den == 1) oss << num;
    else oss << num << "/" << den;
    return oss.str();
}

Rational operator+(const Rational& a, const Rational& b) {
    // a/b + c/d = (ad+bc)/bd
    Rational r(a.num * b.den + b.num * a.den, a.den * b.den);
    r.normalize();
    return r;
}
Rational operator-(const Rational& a, const Rational& b) {
    Rational r(a.num * b.den - b.num * a.den, a.den * b.den);
    r.normalize();
    return r;
}
Rational operator*(const Rational& a, const Rational& b) {
    Rational r(a.num * b.num, a.den * b.den);
    r.normalize();
    return r;
}
Rational operator/(const Rational& a, const Rational& b) {
    if (b.num == 0) throw std::invalid_argument("Division by zero rational");
    Rational r(a.num * b.den, a.den * b.num);
    r.normalize();
    return r;
}
bool operator==(const Rational& a, const Rational& b) {
    return a.num == b.num && a.den == b.den;
}

int64_t mod_norm(int64_t x, int64_t p) {
    int64_t r = x % p;
    if (r < 0) r += p;
    return r;
}
int64_t mod_add(int64_t a, int64_t b, int64_t p) {
    return mod_norm(mod_norm(a, p) + mod_norm(b, p), p);
}
int64_t mod_sub(int64_t a, int64_t b, int64_t p) {
    return mod_norm(mod_norm(a, p) - mod_norm(b, p), p);
}
int64_t mod_mul(int64_t a, int64_t b, int64_t p) {
    // for v large p youd want wider types / montgomery, etc
    __int128 aa = mod_norm(a, p);
    __int128 bb = mod_norm(b, p);
    __int128 rr = (aa * bb) % p;
    return (int64_t)rr;
}

static int64_t egcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int64_t x1 = 0, y1 = 0;
    int64_t g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int64_t mod_inv(int64_t a, int64_t p) {
    a = mod_norm(a, p);
    int64_t x = 0, y = 0;
    int64_t g = egcd(a, p, x, y);
    if (g != 1) throw std::runtime_error("No modular inverse exists (not coprime).");
    return mod_norm(x, p);
}

