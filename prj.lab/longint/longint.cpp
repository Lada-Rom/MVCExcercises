#include "longint.h"
#include <vector>
#include <sstream>

namespace tolstenko_l_s {

LongInt::LongInt(int value) {

    assert(sizeof(m_data) >= sizeof(value));

    if (value < 0) {
       for (auto& e : m_data) {
           e = UDigit(-1);
       }
    }

    reinterpret_cast<int&> (m_data[0]) = value;
}

LongInt::operator bool() const {
    for (auto e : m_data) {
        if (e) {
            return true;
        }
    }
    return false;
}

LongInt operator/(const LongInt& lhs, int rhs) {
    LongInt t(lhs);
    t /= rhs;
    return t;
}

void LongInt::borrowBit(size_t pos) {

    for (size_t i = pos; i < m_data.size(); ++i)
    {
        if (m_data[i]--)
            break;
    }
}

int LongInt::DivWithRemainder(int denom) {

    std::lldiv_t q{ 0, IsNegative() ? -1 : 0 };

    for (size_t i = m_data.size(); i--;)
    {
        const auto nom = m_data[i] + (q.rem << wordBit);
        q = std::lldiv(nom, denom);
        m_data[i] = UDigit(q.quot);
        if (q.quot < 0)
        {
            borrowBit(i + 1);
        }
    }
    return int(q.rem);
}

std::string LongInt::ToString() const
{
    const auto radixDenom = 1000000000;

    std::vector<int> vec;

    for (LongInt t(*this); t;) {
        auto rem = t.DivWithRemainder(radixDenom);
        vec.push_back(std::abs(rem));
    }

    std::ostringstream output;
    if (IsNegative())
        output << '-';

    for (auto i = vec.rbegin(); i != vec.rend(); ++i) {
        output << *i;
    }
    return output.str();
}

std::ostream& operator<<(std::ostream& ostrm, const LongInt& rhs) {

    return ostrm << rhs.ToString();
}

} //namespace tolstenko_l_s

