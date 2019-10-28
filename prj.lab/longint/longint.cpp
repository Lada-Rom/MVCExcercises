#include "longint.h"

#include <algorithm>
#include <vector>
#include <sstream>


namespace tolstenko_l_s {

void LongInt::normalize()
{
    const auto rbegin = std::find_if(m_data.rbegin(), m_data.rend(),
        [](UDigit digit) { return digit != 0; });

    const auto size = std::max(size_t(1), size_t(m_data.rend() - rbegin));

    if (size != m_data.size())
    {
        m_data.resize(size);
    }
    if (size == 1 && !m_data[0])
    {
        m_isNegative = false;
    }
}

LongInt::LongInt(int value)
: m_data(std::max(size_t(1), sizeof(value) / sizeof(UDigit)))
, m_isNegative(value < 0)
{
    reinterpret_cast<int&>(m_data[0]) = std::abs(value);
    normalize();
}

int LongInt::DivWithRemainder(int denom) {

    if (denom < 0)
    {
        denom = -denom;
        m_isNegative = !m_isNegative;
    }

    lldiv_t q {};

    for (size_t i = m_data.size(); i--;)
    {
        q = std::lldiv(m_data[i] + q.rem * digitRank, denom);
        m_data[i] = UDigit(q.quot);
    }
    normalize();

    return int(q.rem);
}

std::string LongInt::ToString() const {
    const auto radixDenom = 1000000000;

    std::vector<int> vec;

    for (LongInt t(*this); t;) {
        auto rem = t.DivWithRemainder(radixDenom);
        vec.push_back(std::abs(rem));
    }

    std::ostringstream output;
    if (m_isNegative)
        output << '-';

    for (auto i = vec.rbegin(); i != vec.rend(); ++i) {
        output << *i;
    }
    return output.str();
}

// LongInt& LongInt::operator+=(int inputValue)
// {
//     const int addend = m_isNegative ? -inputValue : inputValue;
// 
// 
// }

LongInt& LongInt::operator*=(int inputValue) {

    m_isNegative = m_isNegative != (inputValue < 0);
    const uint32_t multiplier = std::abs(inputValue);

    uint64_t carry {};

    for (auto& e : m_data)
    {
        carry += e * multiplier;
        e = UDigit(carry);
        carry >>= digitBit;
    }
    while (carry)
    {
        m_data.push_back(UDigit(carry));
        carry >>= digitBit;
    }
    return *this;
}

LongInt& LongInt::operator/=(int denom) {
    DivWithRemainder(denom);
    return *this;
}

bool operator==(const LongInt& lhs, const LongInt& rhs)
{
    return lhs.m_isNegative == rhs.m_isNegative && lhs.m_data == rhs.m_data;
}

LongInt operator / (LongInt lhs, int rhs) {
    lhs /= rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& ostrm, const LongInt& rhs) {
    return ostrm << rhs.ToString();
}

} //namespace tolstenko_l_s

