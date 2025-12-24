#ifndef ELLIPTIC_CURVE_CALC_H
#define ELLIPTIC_CURVE_CALC_H

#include "math_utils.h"
#include <string>

struct Curve {
    FieldType field{FieldType::FINITE_FP};

    // for F_p: use a_fp, b_fp, p
    int64_t a_fp{0};
    int64_t b_fp{0};
    int64_t p{0};

    // for R: use a_real, b_real
    double a_real{0.0};
    double b_real{0.0};

    // for Q: use a_q, b_q
    Rational a_q{0};
    Rational b_q{0};
};

struct ECPoint {
    bool infinity{true};

    // for F_p
    int64_t x_fp{0};
    int64_t y_fp{0};

    // for R
    double x_real{0.0};
    double y_real{0.0};

    // for Q
    Rational x_q{0};
    Rational y_q{0};

    static ECPoint Infinity() { return ECPoint(); }

    std::string toString(const Curve& c) const;
};

bool isOnCurve(const Curve& c, const ECPoint& P);

// group operation
ECPoint addPoints(const Curve& c, const ECPoint& P, const ECPoint& Q);
ECPoint scalarMultiply(const Curve& c, const ECPoint& P, int64_t n);

#endif

