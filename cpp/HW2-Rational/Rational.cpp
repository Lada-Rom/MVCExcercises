#include <iostream>
#include <sstream>

class Rational
{
public:
    Rational() = default;
    Rational(int num, int denom);

    int num() const { return numerator; }
    int denom() const {return denominator; }

    Rational& operator += (const Rational&);
    Rational& operator -= (const Rational&);
    Rational& operator *= (const Rational&);
    Rational& operator /= (const Rational&);

private:
    int numerator{0};
    int denominator{1};
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
void testParse(const std::string&);


//----------------------------------------------------------
int main()
try
{
    using std::cout;
    using std::endl;

    #define PRINT(expr) (std::cout << #expr " => " << (expr) << std::endl)

    Rational f; 

    PRINT(f += Rational(3, 5));
    PRINT(f -= Rational(2, 5));
    PRINT(f += Rational(4, 10));
    PRINT(f *= Rational(5, 1));
    PRINT(f /= Rational(1, -3));

    try
    {
        PRINT(f += Rational(4, 0));
    }
    catch(const std::invalid_argument& ex)
    {
        cout << "Expected exception caught: " << ex.what() << endl;
    }
    cout << endl;

    testParse("2/5");
    testParse("2/-5");

    cout << endl;

    cout << std::boolalpha;
    PRINT(Rational(2, 4) == Rational(3, 6));
    PRINT(Rational(-2, 4) == Rational(3, -6));
    PRINT(Rational(2, 4) != Rational(3, 6));
    PRINT(Rational(1, 5) >= Rational(2, 10));
    PRINT(Rational(1, 5) > Rational(2, 10));
    PRINT(Rational(1, 5) < Rational(2, 10));
    PRINT(Rational(1, 2) <= Rational(1, 3));
    PRINT(Rational(1, 0) == Rational(2, 10));

    #undef PRINT
}
catch(const std::exception& ex)
{
    std::cerr << "ERROR: " << ex.what() << std::endl;
}
//----------------------------------------------------------

Rational::Rational(int num, int denom) : numerator(num), denominator(denom)
{
    if (denom == 0)
    {
        throw std::invalid_argument("Zero denominator");
    }
}

std::ostream& operator << (std::ostream& ostrm, const Rational& f)
{
    ostrm << f.num();
    if (f.denom() != 1)
    {
        ostrm << '/' << f.denom();
    }
    return ostrm;
}

std::istream& operator >> (std::istream& istrm, Rational& f)
{
    int numenator = 0;
    int denominator = 1;

    if (istrm >> numenator)
    {
        char symbol = 0;
        if (istrm >> symbol)
            if (symbol == '/') istrm >> denominator;
            else istrm.unget();
    }
    f = reduce(numenator, denominator);
    return istrm;
}


Rational operator + (const Rational& x, const Rational& y)
{
    return reduce(x.num() * y.denom() + y.num() * x.denom(), x.denom() * y.denom());
}

Rational operator - (const Rational& x, const Rational& y)
{
    return reduce(x.num() * y.denom() - y.num() * x.denom(), x.denom() * y.denom());
}

Rational operator * (const Rational& x, const Rational& y)
{
    return reduce(x.num() * y.num(), x.denom() * y.denom());
}

Rational operator / (const Rational& x, const Rational& y)
{
    return reduce(x.num() * y.denom(), x.denom() * y.num());
}


Rational& Rational::operator += (const Rational& rhs)
{
    return *this = *this + rhs;
}

Rational& Rational::operator -= (const Rational& rhs)
{
    return *this = *this - rhs;
}

Rational& Rational::operator *= (const Rational& rhs)
{
    return *this = *this * rhs;
}

Rational& Rational::operator /= (const Rational& rhs)
{
    return *this = *this / rhs;
}


bool operator == (const Rational& x, const Rational& y)
{
    return (x.num() * y.denom() == x.denom() * y.num());
}

bool operator != (const Rational& x, const Rational& y)
{
    return !(x == y);
}

bool operator > (const Rational& x, const Rational& y)
{
    return (x.num() * y.denom() > x.denom() * y.num());
}

bool operator < (const Rational& x, const Rational& y)
{
    return (y > x);
}

bool operator >= (const Rational& x, const Rational& y)
{
    return !(x < y);
}

bool operator <= (const Rational& x, const Rational& y)
{
    return !(x > y);
}


int gcd(const int x, const int y)
{
    return y ? gcd(y, x % y) : std::abs(x);
}

Rational reduce(const int x, const int y)
{
    int g = gcd(x, y);
    if (y < 0) g = -g;
    return {x / g, y / g};
}

Rational reduce(const Rational& f)
{
    return reduce(f.num(), f.denom());
}

void testParse(const std::string& str)
{
    using namespace std;
    istringstream istrm(str);
    Rational f;
    istrm >> f;
    if (istrm) 
    {
        cout << "Read success: " << str << " -> " << f << endl;
    }
    else 
    {
        cout << "Read error : " << str << " -> " << f << endl;
    }
}