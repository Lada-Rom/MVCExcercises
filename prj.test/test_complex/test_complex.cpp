#include <complex/complex.h>
#include <sstream>

namespace {

bool testParse(const std::string& str) {
    using std::cout;
    using std::endl;
    using std::istringstream;

    istringstream istrm(str);
    Complex z;
    istrm >> z;
    if (istrm.good()) {
        cout << "Read success: " << str << " -> " << z << endl;
    }
    else {
        cout << "Read error: " << str << " -> " << z << endl;
    }
    return istrm.good();
}

} //namespace

int main() {
    using std::cout;
    using std::endl;

    Complex z;
    z += Complex(2.5, 1.5);
    cout << z << endl;

    z *= Complex(2, 1);
    cout << z << endl;

    z -= Complex(2, 1);
    cout << z << endl;

    testParse("{8.9,9}");
    testParse("{8.9, 9}");
    testParse("{8.9,9");
}
