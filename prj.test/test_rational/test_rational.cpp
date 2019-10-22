#include <rational/rational.h>

namespace {

void testParse(const std::string& str) {
    using std::istringstream;
    using std::cout;
    using std::endl;

    istringstream istrm(str);
    Rational f;
    istrm >> f;
    if (istrm) {
        cout << "Read success: " << str << " -> " << f << endl;
    }
    else {
        cout << "Read error : " << str << " -> " << f << endl;
    }
}

} //namespace

int main()
try {
    using std::cout;
    using std::endl;

#define PRINT(expr) (std::cout << #expr " => " << (expr) << std::endl)

    Rational f;

    PRINT(f += Rational(3, 5));
    PRINT(f -= Rational(2, 5));
    PRINT(f += Rational(4, 10));
    PRINT(f *= Rational(5, 1));
    PRINT(f /= Rational(1, -3));

    try {
        PRINT(f += Rational(4, 0));
    }
    catch (const std::invalid_argument& ex) {
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
catch (const std::exception& ex) {
    std::cerr << "ERROR: " << ex.what() << std::endl;
}