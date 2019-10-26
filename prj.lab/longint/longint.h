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

    explicit operator bool() const;

    bool IsNegative() const { return SDigit(rdata(0)) < 0; }

    LongInt& operator/=(int denom) { DivWithRemainder(denom); return *this; }

    int DivWithRemainder(int);

private:

    using UDigit = uint8_t;
    using SDigit = int8_t;
    static const auto wordBit = sizeof(UDigit) * CHAR_BIT;

    friend LongInt operator+(const LongInt&, const LongInt&);
    friend LongInt operator-(const LongInt&, const LongInt&);
    friend LongInt operator*(const LongInt&, const LongInt&);
    friend LongInt operator/(const LongInt&, int);

    friend std::ostream& operator<<(std::ostream&, const LongInt&);
    friend std::istream& operator>>(std::istream&, LongInt&);

    size_t dataSize() const { return data.size(); }

    void borrowBit(size_t);

    UDigit& rdata(size_t i) {
        assert(i < dataSize());
        return data[dataSize() - i - 1];
    }

    const UDigit& rdata(size_t i) const {
        assert(i < dataSize());
        return data[dataSize() - i - 1];
    }

    std::vector<UDigit> data = std::vector<UDigit>(8, 0);
};

LongInt operator+(const LongInt&, const LongInt&);
LongInt operator-(const LongInt&, const LongInt&);
LongInt operator*(const LongInt&, const LongInt&);
LongInt operator/(const LongInt&, int);

std::ostream& operator<<(std::ostream&, const LongInt&);
std::istream& operator>>(std::istream&, LongInt&);

} //namespace tolstenko_l_s

#endif
