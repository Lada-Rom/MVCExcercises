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

Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.re * rhs.re - lhs.im * rhs.im,
        rhs.re * lhs.im + lhs.re * rhs.im);
}

Complex& Complex::operator*=(const Complex& rhs) {
    return *this = *this * rhs;
}

Complex& Complex::operator*=(const double rhs) {
    re *= rhs;
    im *= rhs;
    return *this;
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
