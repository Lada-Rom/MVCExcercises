// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef RATIONAL_RATIONAL_H_20192210
#define RATIONAL_RATIONAL_H_20192210

#include <iostream>
#include <sstream>
#include <string>

class Rational {
public:
    Rational() = default;
    Rational(int num, int denom);

    int num() const { return numerator; }
    int denom() const { return denominator; }

    Rational& operator += (const Rational&);
    Rational& operator -= (const Rational&);
    Rational& operator *= (const Rational&);
    Rational& operator /= (const Rational&);

private:
    int numerator{ 0 };
    int denominator{ 1 };
};

std::ostream& operator << (std::ostream&, const Rational&);
std::istream& operator >> (std::istream&, Rational&);

Rational operator + (const Rational&, const Rational&);
Rational operator - (const Rational&, const Rational&);
Rational operator * (const Rational&, const Rational&);
Rational operator / (const Rational&, const Rational&);

bool operator == (const Rational&, const Rational&);
bool operator != (const Rational&, const Rational&);
bool operator < (const Rational&, const Rational&);
bool operator > (const Rational&, const Rational&);
bool operator <= (const Rational&, const Rational&);
bool operator >= (const Rational&, const Rational&);

int gcd(const int, const int);
Rational reduce(const Rational&);
Rational reduce(const int, const int);

#endif