#include "rational.h"

Rational::Rational(int num, int denom) : num_(num), denom_(denom) {
    if (denom == 0) {
        throw std::invalid_argument("Zero denominator");
    }
}

Rational Rational::parse(const std::string& str) {
    const auto slash_pos = str.find_first_not_of("-0123456789");

    if(slash_pos == std::string::npos || str[slash_pos] != '/')
        throw std::invalid_argument("Invalid Rational format: " + str);

    const auto parse_number = [](const std::string& str) {
        std::istringstream input(str);
        int value{};
        input >> value;
        return value;
    };

    const auto num = parse_number(str.substr(0, slash_pos));
    const auto end_pos = str.find_first_not_of("0123456789", slash_pos + 1);

    if (end_pos != std::string::npos)
        throw std::invalid_argument("Invalid Rational format: " + str);

    const auto denom = parse_number(str.substr(slash_pos + 1));

    return reduce(num, denom);
}

std::ostream& operator << (std::ostream& ostrm, const Rational& f) {
    return ostrm << f.num() << '/' << f.denom();
}

std::istream& operator >> (std::istream& istrm, Rational& f) {
    try {
        std::string str;
        if (istrm >> str) {
            f = Rational::parse(str);
        }
    }
    catch(const std::invalid_argument&) {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}

Rational Rational::operator - () const {
    return reduce(-num_, denom_);
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
