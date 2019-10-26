#include "longint.h"
#include <vector>

namespace tolstenko_l_s {

LongInt::LongInt(int value) {
    assert(sizeof(data) >= sizeof(value));

    if (value < 0) {
        for (auto& e : data)
            e = -1;
    }

    reinterpret_cast<int&> (data[0]) = value;
}

LongInt::operator bool() const {
    for (auto e : data) {
        if (e) 
            return true;
    }
    return false;
}

LongInt operator/(const LongInt& lhs, int rhs) {
    LongInt t(lhs);
    t /= rhs;
    return t;
}

std::ostream& operator<<(std::ostream& ostrm, const LongInt& rhs) {

    std::vector<int> vec;

    for (LongInt t(rhs); t;){
        auto rem = t.DivWithRemainder(10);
        vec.push_back(std::abs(rem));
    }

    if (rhs.IsNegative()) 
        ostrm << '-';

    for (auto i = vec.rbegin(); i != vec.rend(); ++i) {
        ostrm << *i;
    }

    return ostrm;
}

void LongInt::borrowBit(size_t pos) {

    for (size_t i = pos; i < dataSize(); ++i)
    {
        if (data[i]--)
            break;
    }
}

int LongInt::DivWithRemainder(int denom) {

    std::lldiv_t q{ 0, IsNegative() ? -1 : 0 };

    for (size_t i = dataSize(); i--;)
    {
        const auto nom = data[i] + (q.rem << wordBit);
        q = std::lldiv(nom, denom);
        data[i] = UDigit(q.quot);
        if (q.quot < 0)
        {
            borrowBit(i + 1);
        }
    }
    return int(q.rem);
}

} //namespace tolstenko_l_s

