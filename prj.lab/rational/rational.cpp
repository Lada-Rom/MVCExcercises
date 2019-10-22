#include "rational.h"

Rational::Rational(int num, int denom) : numerator(num), denominator(denom) {
    if (denom == 0) {
        throw std::invalid_argument("Zero denominator");
    }
}

std::ostream& operator << (std::ostream& ostrm, const Rational& f) {
    ostrm << f.num();
    if (f.denom() != 1) {
        ostrm << '/' << f.denom();
    }
    return ostrm;
}

std::istream& operator >> (std::istream& istrm, Rational& f) {
    int numenator = 0;
    int denominator = 1;

    if (istrm >> numenator) {
        char symbol = 0;
        if (istrm >> symbol) {
            if (symbol == '/') {
                istrm >> denominator;
            }
            else {
                istrm.unget();
            }
        }
    }
    f = reduce(numenator, denominator);
    return istrm;
}

Rational operator + (const Rational& x, const Rational& y) {
    return reduce(x.num() * y.denom() + y.num() * x.denom(),
        x.denom() * y.denom());
}

Rational operator - (const Rational& x, const Rational& y) {
    return reduce(x.num() * y.denom() - y.num() * x.denom(),
        x.denom() * y.denom());
}

Rational operator * (const Rational& x, const Rational& y) {
    return reduce(x.num() * y.num(), x.denom() * y.denom());
}

Rational operator / (const Rational& x, const Rational& y) {
    return reduce(x.num() * y.denom(), x.denom() * y.num());
}

Rational& Rational::operator += (const Rational& rhs) {
    return *this = *this + rhs;
}

Rational& Rational::operator -= (const Rational& rhs) {
    return *this = *this - rhs;
}

Rational& Rational::operator *= (const Rational& rhs) {
    return *this = *this * rhs;
}

Rational& Rational::operator /= (const Rational& rhs) {
    return *this = *this / rhs;
}


bool operator == (const Rational& x, const Rational& y) {
    return (x.num() * y.denom() == x.denom() * y.num());
}

bool operator != (const Rational& x, const Rational& y) {
    return !(x == y);
}

bool operator > (const Rational& x, const Rational& y) {
    return (x.num() * y.denom() > x.denom() * y.num());
}

bool operator < (const Rational& x, const Rational& y) {
    return (y > x);
}

bool operator >= (const Rational& x, const Rational& y) {
    return !(x < y);
}

bool operator <= (const Rational& x, const Rational& y) {
    return !(x > y);
}

int gcd(const int x, const int y) {
    return y ? gcd(y, x % y) : std::abs(x);
}

Rational reduce(const int x, const int y) {
    int g = gcd(x, y);
    if (y < 0)
        g = -g;
    return{ x / g, y / g };
}

Rational reduce(const Rational& f) {
    return reduce(f.num(), f.denom());
}
