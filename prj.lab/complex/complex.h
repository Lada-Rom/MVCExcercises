// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef COMPLEX_COMPLEX_H_20192210
#define COMPLEX_COMPLEX_H_20192210

#include <iostream>

struct Complex {
    Complex() {}
    explicit Complex(const double real);
    Complex(const double real, const double imaginary);
    bool operator==(const Complex& rhs) const {
        return (re == rhs.re) && (im == rhs.im);
    }

    bool operator!=(const Complex& rhs) const { return !operator==(rhs); }
    Complex& operator+=(const Complex& rhs);
    Complex& operator+=(const double rhs) { return operator+=(Complex(rhs)); }

    Complex& operator-=(const Complex& rhs) {
        re -= rhs.re; im -= rhs.im; return *this;
    }
    Complex& operator-=(const double rhs) { return operator-=(Complex(rhs)); }

    Complex& operator*=(const Complex& rhs);
    Complex& operator*=(const double rhs);

    Complex& operator/=(const Complex& rhs);
    Complex& operator/=(const double rhs);

    Complex operator - () const { return {-re, -im}; }

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);

    double re{ 0.0 };
    double im{ 0.0 };

    static const char leftBrace{ '{' };
    static const char separator{ ',' };
    static const char rightBrace{ '}' };
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator+(const Complex& lhs, const double rhs);
Complex operator+(const double lhs, const Complex& rhs);

Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const double rhs);
Complex operator-(const double lhs, const Complex& rhs);

Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const double rhs);
Complex operator*(const double lhs, const Complex& rhs);

Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const double rhs);
Complex operator/(const double lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs);
std::istream& operator>>(std::istream& istrm, Complex& rhs);

#endif
