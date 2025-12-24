#include <iostream>
#include <string>
#include <limits>
#include "ellipticCurveCalculations.h"

static void clearLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int64_t readInt64(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        long long v;
        if (std::cin >> v) return (int64_t)v;
        std::cin.clear();
        clearLine();
        std::cout << "Invalid integer. Try again.\n";
    }
}

static double readDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        double v;
        if (std::cin >> v) return v;
        std::cin.clear();
        clearLine();
        std::cout << "Invalid number. Try again.\n";
    }
}

static Rational readRational(const std::string& prompt) {
    // accepts either an integer or fraction
    while (true) {
        std::cout << prompt;
        std::string s;
        if (!(std::cin >> s)) throw std::runtime_error("Input failed.");

        auto slash = s.find('/');
        try {
            if (slash == std::string::npos) {
                int64_t n = std::stoll(s);
                return Rational(n);
            } else {
                int64_t n = std::stoll(s.substr(0, slash));
                int64_t d = std::stoll(s.substr(slash + 1));
                return Rational(n, d);
            }
        } catch (...) {
            std::cout << "Invalid rational. Use e.g. 5 or -3/7\n";
        }
    }
}

static ECPoint readPoint(const Curve& c, const std::string& name) {
    std::cout << "Enter point " << name << " (or type O for infinity).\n";
    std::cout << "First token: ";
    std::string first;
    std::cin >> first;
    if (first == "O" || first == "o") return ECPoint::Infinity();

    ECPoint P;
    P.infinity = false;

    if (c.field == FieldType::FINITE_FP) {
        int64_t x = std::stoll(first);
        int64_t y = readInt64("Second token (y): ");
        P.x_fp = mod_norm(x, c.p);
        P.y_fp = mod_norm(y, c.p);
    } else if (c.field == FieldType::REALS) {
        double x = std::stod(first);
        double y = readDouble("Second token (y): ");
        P.x_real = x;
        P.y_real = y;
    } else {
        // first might be rational
        auto slash = first.find('/');
        Rational x;
        if (slash == std::string::npos) x = Rational(std::stoll(first));
        else x = Rational(std::stoll(first.substr(0, slash)), std::stoll(first.substr(slash + 1)));

        Rational y = readRational("Second token (y) (e.g. 2 or 5/3): ");
        P.x_q = x;
        P.y_q = y;
    }

    return P;
}

static Curve readCurve() {
    Curve c;

    std::cout << "Choose field:\n";
    std::cout << "  1) Finite field F_p\n";
    std::cout << "  2) Real numbers R\n";
    std::cout << "  3) Rational numbers Q\n";
    int choice = (int)readInt64("Your choice: ");

    if (choice == 1) {
        c.field = FieldType::FINITE_FP;
        c.p = readInt64("Enter prime p: ");
        c.a_fp = readInt64("Enter a (mod p): ");
        c.b_fp = readInt64("Enter b (mod p): ");
        c.a_fp = mod_norm(c.a_fp, c.p);
        c.b_fp = mod_norm(c.b_fp, c.p);
        std::cout << "Curve: y^2 = x^3 + ax + b (mod p)\n";
    } else if (choice == 2) {
        c.field = FieldType::REALS;
        c.a_real = readDouble("Enter a: ");
        c.b_real = readDouble("Enter b: ");
        std::cout << "Curve: y^2 = x^3 + ax + b over R\n";
    } else {
        c.field = FieldType::RATIONALS;
        c.a_q = readRational("Enter a (e.g. 2 or -3/7): ");
        c.b_q = readRational("Enter b (e.g. 5 or 1/2): ");
        std::cout << "Curve: y^2 = x^3 + ax + b over Q\n";
    }

    return c;
}

int main() {
    try {
        std::cout << "Elliptic Curve Calculator\n";
        std::cout << "-------------------------\n";

        Curve c = readCurve();

        std::cout << "\nChoose operation:\n";
        std::cout << "  1) Add two points: P + Q\n";
        std::cout << "  2) Multiply a point: n * P (doubling/tripling/quadrupling/etc)\n";
        int op = (int)readInt64("Your choice: ");

        if (op == 1) {
            ECPoint P = readPoint(c, "P");
            ECPoint Q = readPoint(c, "Q");

            if (!isOnCurve(c, P) || !isOnCurve(c, Q)) {
                std::cout << "Warning: One or both points are not on the curve.\n";
            }

            ECPoint R = addPoints(c, P, Q);
            std::cout << "\nP = " << P.toString(c) << "\n";
            std::cout << "Q = " << Q.toString(c) << "\n";
            std::cout << "P + Q = " << R.toString(c) << "\n";
        } else if (op == 2) {
            int64_t n = readInt64("Enter n (e.g. 2 for double, 3 for triple, ...): ");
            ECPoint P = readPoint(c, "P");

            if (!isOnCurve(c, P)) {
                std::cout << "Warning: Point is not on the curve.\n";
            }

            ECPoint R = scalarMultiply(c, P, n);
            std::cout << "\nP = " << P.toString(c) << "\n";
            std::cout << n << " * P = " << R.toString(c) << "\n";
        } else {
            std::cout << "Unknown operation.\n";
            return 1;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}

