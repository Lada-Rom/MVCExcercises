// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef LONGINT_LONGINT_H_20192610
#define LONGINT_LONGINT_H_20192610

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace tolstenko_l_s {

class LongInt {
public:

    LongInt() = default;
    LongInt(int);

    int DivWithRemainder(int);

    std::string ToString() const;

    explicit operator bool() const { return m_digits.back() != 0; }

    LongInt& operator+=(const LongInt&);
    LongInt& operator*=(int);
    LongInt& operator/=(int);

    friend LongInt operator+(const LongInt&, const LongInt&);
    friend LongInt operator-(const LongInt&, const LongInt&);
    friend LongInt operator*(const LongInt&, const LongInt&);
    friend LongInt operator / (LongInt, int);

    friend bool operator==(const LongInt&, const LongInt&);
    friend bool operator!=(const LongInt&, const LongInt&);
    friend bool operator<(const LongInt&, const LongInt&);
    friend bool operator>(const LongInt&, const LongInt&);
    friend bool operator<=(const LongInt&, const LongInt&);
    friend bool operator>=(const LongInt&, const LongInt&);

    friend std::ostream& operator<<(std::ostream&, const LongInt&);
    friend std::istream& operator>>(std::istream&, LongInt&);

private:

    using Digit = uint8_t;
    using Digits = std::vector<Digit>;

    static constexpr const auto digitBit = sizeof(Digit) * CHAR_BIT;

    void normalize();
    static void negate(Digits&);

    Digits m_digits {0};
    bool m_isNegative = false;
};

LongInt operator+(const LongInt&, const LongInt&);
LongInt operator-(const LongInt&, const LongInt&);
LongInt operator*(const LongInt&, const LongInt&);


std::ostream& operator<<(std::ostream&, const LongInt&);
std::istream& operator>>(std::istream&, LongInt&);

} //namespace tolstenko_l_s

#endif
