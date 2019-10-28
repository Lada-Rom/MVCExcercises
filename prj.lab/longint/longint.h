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

    explicit operator bool() const { return m_data.back() != 0; }

    LongInt& operator+=(int);
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

    using UDigit = uint8_t;
    using SDigit = std::make_signed_t<UDigit>;
    static constexpr const auto digitBit = sizeof(UDigit) * CHAR_BIT;
    static constexpr const auto digitRank = 1 << digitBit;

    void normalize();

    std::vector<UDigit> m_data {0};
    bool m_isNegative = false;
};

LongInt operator+(const LongInt&, const LongInt&);
LongInt operator-(const LongInt&, const LongInt&);
LongInt operator*(const LongInt&, const LongInt&);


std::ostream& operator<<(std::ostream&, const LongInt&);
std::istream& operator>>(std::istream&, LongInt&);

} //namespace tolstenko_l_s

#endif
