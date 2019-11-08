#include "complex.h"
#include <sstream>

std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs) {
    return rhs.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Complex& rhs) {
    return rhs.readFrom(istrm);
}

Complex::Complex(const double real)
    : Complex(real, 0.0) {
}

Complex::Complex(const double real, const double imaginary)
    : re(real)
    , im(imaginary) {
}

Complex& Complex::operator+=(const Complex& rhs) {
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex sum(lhs);
    sum += rhs;
    return sum;
}

Complex operator+(const Complex& lhs, const double rhs) {
    return lhs + Complex(rhs);
}

Complex operator+(const double lhs, const Complex& rhs) {
    return Complex(lhs) + rhs;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

Complex operator-(const Complex& lhs, const double rhs) {
    return lhs - Complex(rhs);
}

Complex operator-(const double lhs, const Complex& rhs) {
    return Complex(lhs) - rhs;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.re * rhs.re - lhs.im * rhs.im,
        rhs.re * lhs.im + lhs.re * rhs.im);
}

Complex operator*(const Complex& lhs, const double rhs) {
    return { lhs.re * rhs, lhs.im * rhs };
}

Complex operator*(const double lhs, const Complex& rhs) {
    return Complex(lhs) * rhs;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    const auto denom = rhs.re * rhs.re + rhs.im * rhs.im;
    return { 
        (lhs.re * rhs.re + lhs.im * rhs.im) / denom,
        (lhs.im * rhs.re - lhs.re * rhs.im) / denom
    };
}

Complex operator/(const Complex& lhs, const double rhs) {
    return {lhs.re / rhs, lhs.im / rhs };
}

Complex operator/(const double lhs, const Complex& rhs) {
    return Complex(lhs) / rhs;
}

Complex& Complex::operator*=(const Complex& rhs) {
    return *this = *this * rhs;
}

Complex& Complex::operator*=(const double rhs) {
    re *= rhs;
    im *= rhs;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    return *this = *this / rhs;
}

Complex& Complex::operator/=(const double rhs) {
    return *this = *this / rhs;
}

namespace {

bool epsilon_less(double lhs, double rhs) {
    constexpr const auto epsilon = std::numeric_limits<double>::epsilon();
    return lhs < rhs * (1 + epsilon) && lhs * (1 + epsilon) < rhs;
}

bool epsilon_equal(double lhs, double rhs) {
    return !(epsilon_less(lhs, rhs) || epsilon_less(rhs, lhs));
}

} // namespace

bool Complex::operator == (const Complex& rhs) const {
    return epsilon_equal(re, rhs.re) && epsilon_equal(im, rhs.im);
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const {
    ostrm << leftBrace << re << separator << " " << im << rightBrace;
    return ostrm;
}

std::istream& Complex::readFrom(std::istream& istrm) {
#pragma warning (push)
#pragma warning (disable: 4458) //declaration of 'leftBrace' hides class member
    char leftBrace(0);
    char rightBrace(0);
#pragma warning (pop)
    double real(0.0);
    char comma(0);
    double imaganary(0.0);

    istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
    if (istrm.good()) {
        if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma)
            && (Complex::rightBrace == rightBrace)) {
            re = real;
            im = imaganary;
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}
