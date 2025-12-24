#include "ellipticCurveCalculations.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

static constexpr double EPS = 1e-12;

std::string ECPoint::toString(const Curve& c) const {
    if (infinity) return "O (point at infinity)";
    std::ostringstream oss;
    oss << "(";
    if (c.field == FieldType::FINITE_FP) {
        oss << x_fp << ", " << y_fp;
    } else if (c.field == FieldType::REALS) {
        oss << x_real << ", " << y_real;
    } else {
        oss << x_q.toString() << ", " << y_q.toString();
    }
    oss << ")";
    return oss.str();
}

bool isOnCurve(const Curve& c, const ECPoint& P) {
    if (P.infinity) return true;

    if (c.field == FieldType::FINITE_FP) {
        int64_t p = c.p;
        int64_t left = mod_mul(P.y_fp, P.y_fp, p);
        int64_t x2 = mod_mul(P.x_fp, P.x_fp, p);
        int64_t x3 = mod_mul(x2, P.x_fp, p);
        int64_t right = mod_add(mod_add(x3, mod_mul(c.a_fp, P.x_fp, p), p), c.b_fp, p);
        return left == right;
    } else if (c.field == FieldType::REALS) {
        double left = P.y_real * P.y_real;
        double right = P.x_real*P.x_real*P.x_real + c.a_real*P.x_real + c.b_real;
        return std::fabs(left - right) < 1e-9;
    } else {
        // Q
        Rational left = P.y_q * P.y_q;
        Rational right = (P.x_q * P.x_q * P.x_q) + (c.a_q * P.x_q) + c.b_q;
        return left == right;
    }
}

// finite field add(short Weierstrass y^2 = x^3 + ax + b)
static ECPoint addFp(const Curve& c, const ECPoint& P, const ECPoint& Q) {
    if (P.infinity) return Q;
    if (Q.infinity) return P;

    int64_t p = c.p;

    int64_t x1 = mod_norm(P.x_fp, p), y1 = mod_norm(P.y_fp, p);
    int64_t x2 = mod_norm(Q.x_fp, p), y2 = mod_norm(Q.y_fp, p);

    // P + (-P) = O
    if (x1 == x2 && mod_add(y1, y2, p) == 0) return ECPoint::Infinity();

    int64_t lambda = 0;

    if (x1 == x2 && y1 == y2) {
        // doubling: lambda = (3x1^2 + a) / (2y1)
        int64_t num = mod_add(mod_mul(3, mod_mul(x1, x1, p), p), c.a_fp, p);
        int64_t den = mod_mul(2, y1, p);
        lambda = mod_mul(num, mod_inv(den, p), p);
    } else {
        // addition: lambda = (y2 - y1) / (x2 - x1)
        int64_t num = mod_sub(y2, y1, p);
        int64_t den = mod_sub(x2, x1, p);
        lambda = mod_mul(num, mod_inv(den, p), p);
    }

    int64_t x3 = mod_sub(mod_sub(mod_mul(lambda, lambda, p), x1, p), x2, p);
    int64_t y3 = mod_sub(mod_mul(lambda, mod_sub(x1, x3, p), p), y1, p);

    ECPoint R;
    R.infinity = false;
    R.x_fp = x3;
    R.y_fp = y3;
    return R;
}

// add on R
static ECPoint addReals(const Curve& c, const ECPoint& P, const ECPoint& Q) {
    if (P.infinity) return Q;
    if (Q.infinity) return P;

    double x1 = P.x_real, y1 = P.y_real;
    double x2 = Q.x_real, y2 = Q.y_real;

    if (std::fabs(x1 - x2) < EPS && std::fabs(y1 + y2) < EPS) return ECPoint::Infinity();

    double lambda = 0.0;
    if (std::fabs(x1 - x2) < EPS && std::fabs(y1 - y2) < EPS) {
        // doubling
        double den = 2.0 * y1;
        if (std::fabs(den) < EPS) return ECPoint::Infinity();
        lambda = (3.0*x1*x1 + c.a_real) / den;
    } else {
        double den = (x2 - x1);
        if (std::fabs(den) < EPS) throw std::runtime_error("Vertical line encountered unexpectedly.");
        lambda = (y2 - y1) / den;
    }

    double x3 = lambda*lambda - x1 - x2;
    double y3 = lambda*(x1 - x3) - y1;

    ECPoint R;
    R.infinity = false;
    R.x_real = x3;
    R.y_real = y3;
    return R;
}

// add on Q
static ECPoint addRationals(const Curve& c, const ECPoint& P, const ECPoint& Q) {
    if (P.infinity) return Q;
    if (Q.infinity) return P;

    Rational x1 = P.x_q, y1 = P.y_q;
    Rational x2 = Q.x_q, y2 = Q.y_q;

    if (x1 == x2 && (y1 + y2) == Rational(0)) return ECPoint::Infinity();

    Rational lambda;
    if (x1 == x2 && y1 == y2) {
        // (3x^2 + a) / (2y)
        Rational den = Rational(2) * y1;
        if (den == Rational(0)) return ECPoint::Infinity();
        lambda = (Rational(3) * x1 * x1 + c.a_q) / den;
    } else {
        Rational den = (x2 - x1);
        if (den == Rational(0)) throw std::runtime_error("Vertical line encountered unexpectedly.");
        lambda = (y2 - y1) / den;
    }

    Rational x3 = lambda*lambda - x1 - x2;
    Rational y3 = lambda*(x1 - x3) - y1;

    ECPoint R;
    R.infinity = false;
    R.x_q = x3;
    R.y_q = y3;
    return R;
}

ECPoint addPoints(const Curve& c, const ECPoint& P, const ECPoint& Q) {
    if (c.field == FieldType::FINITE_FP) return addFp(c, P, Q);
    if (c.field == FieldType::REALS) return addReals(c, P, Q);
    return addRationals(c, P, Q);
}

ECPoint scalarMultiply(const Curve& c, const ECPoint& P, int64_t n) {
    if (n == 0 || P.infinity) return ECPoint::Infinity();

    // handle negative n by using -P
    ECPoint base = P;
    if (n < 0) {
        n = -n;
        if (c.field == FieldType::FINITE_FP) {
            base.y_fp = mod_norm(-base.y_fp, c.p);
        } else if (c.field == FieldType::REALS) {
            base.y_real = -base.y_real;
        } else {
            base.y_q = Rational(-base.y_q.num, base.y_q.den);
        }
    }

    ECPoint result = ECPoint::Infinity();
    ECPoint addend = base;

    while (n > 0) {
        if (n & 1) result = addPoints(c, result, addend);
        addend = addPoints(c, addend, addend);
        n >>= 1;
    }
    return result;
}

