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
    explicit Rational(int num) : Rational(num, 1) {}

    int num() const { return num_; }
    int denom() const { return denom_; }

    Rational operator - () const;

    Rational& operator += (const Rational&);
    Rational& operator -= (const Rational&);
    Rational& operator *= (const Rational&);
    Rational& operator /= (const Rational&);

    static Rational parse (const std::string&);

private:
    int num_{ 0 };
    int denom_{ 1 };
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