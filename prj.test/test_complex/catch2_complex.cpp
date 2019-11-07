#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <complex/complex.h>

#include <array>
#include <limits>
#include <strstream>
#include <utility>

constexpr double delta = std::numeric_limits<double>::epsilon();

std::array<const char*, 4> well_formated{
  "{0,1}", "{13, 3}", "{ -13, 3}", "{1.9e-3, 19.0e2}"
};
std::array<const char*, 6> bad_formated{
  "0,1", "{2/3}", "3", "2.3", "13/-3",
  "-13/-3"
};

Complex conj(const Complex& z) {
    return Complex(z.re, -z.im);
}

TEST_CASE("Complex ctor", "[complex]") {
    CHECK(Complex() == Complex(0.0, 0.0));
    CHECK(Complex(2.0) == Complex(2.0, 0.0));
}

TEST_CASE("Complex copy ctor", "[complex]") {
    Complex z(1, 2);
    Complex z_copy(z);
    CHECK(z == z_copy);
}

TEST_CASE("Complex operator=", "[complex]") {
    Complex z(1, 2);
    Complex z_copy;
    CHECK(z != z_copy);
    z_copy = z;
    CHECK(z == z_copy);
    z_copy = Complex(-1, 0);
    CHECK(z != z_copy);
}

TEST_CASE("Complex operator==", "[complex]") {
    CHECK(Complex(1) == Complex(1 + delta));
    CHECK(Complex(0, 1) == Complex(0, 1 + delta));
    CHECK(Complex(1) == Complex(1 - delta));
    CHECK(Complex(0, 1) == Complex(0, 1 - delta));
    CHECK(Complex(-1) == Complex(-1 + delta));
    CHECK(Complex(0, -1) == Complex(0, -1 + delta));
    CHECK(Complex(-1) == Complex(-1 - delta));
    CHECK(Complex(0, -1) == Complex(0, -1 - delta));
}

TEST_CASE("Complex operator!=", "[complex]") {
    CHECK(Complex(1) != Complex(1 + 2 * delta));
    CHECK(Complex(0, 1) != Complex(0, 1 + 2 * delta));
    CHECK(Complex(1) != Complex(1 - 2 * delta));
    CHECK(Complex(0, 1) != Complex(0, 1 - 2 * delta));
}

TEST_CASE("Complex operator>>", "[complex]") {
    for (const auto& str : well_formated) {
        std::istringstream istrm(str);
        Complex z;
        istrm >> z;
        CHECK(istrm.good());
    }

    for (const auto& str : bad_formated) {
        std::istringstream istrm(str);
        Complex z;
        istrm >> z;
        CHECK(istrm.fail());
    }
}

TEST_CASE("Complex operator<< and operator>>", "[complex]") {
    std::ostringstream ostrm;
    Complex z;
    ostrm << z;
    Complex z_from_text;
    std::istringstream istrm(ostrm.str());
    istrm >> z;
    CHECK(istrm.good());
    CHECK(z == z_from_text);

    for (const auto& str : well_formated) {
        CHECK_THAT(str,
            Catch::Matchers::Predicate<std::string>(
                [](std::string const& str) -> bool {
            std::istringstream istrm(str);
            Complex z;
            istrm >> z;
            return istrm.good();
        },
                "Right input should cause srtream good state.")
        );
    }

    for (const auto& str : bad_formated) {
        CHECK_THAT(str,
            Catch::Matchers::Predicate<std::string>(
                [](std::string const& str) -> bool {
            std::istringstream istrm(str);
            Complex z;
            istrm >> z;
            return istrm.fail();
        },
                "Bad input should cause fail srtream state.")
        );
    }
}

TEST_CASE("Complex conj", "[complex]") {
    CHECK(Complex(1) == conj(Complex(1)));
    CHECK(Complex(0, 1) == -conj(Complex(0, 1)));
}

TEST_CASE("Complex unary operator-", "[complex]") {
    CHECK(Complex(-1, 2) == -Complex(1, -2));
}

TEST_CASE("Complex operator+=", "[complex]") {
    CHECK(Complex(1, 2) == (Complex(0, 2) += 1));
    CHECK(Complex(1, 2) == (Complex(0, 2) += Complex(1)));
    CHECK(Complex(0, 1) == (Complex{} += Complex(0, 1)));
}

TEST_CASE("Complex operator+", "[complex]") {
    CHECK(Complex(1, 2) == (Complex(0, 2) + 1));
    CHECK(Complex(1, 2) == (Complex(0, 2) + Complex(1)));
    CHECK(Complex(0, 1) == (Complex() + Complex(0, 1)));
}

TEST_CASE("Complex operator-=", "[complex]") {
    CHECK(Complex(-1, 2) == (Complex(0, 2) -= 1));
    CHECK(Complex(1, 1) == (Complex(2, 1) -= Complex(1)));
    CHECK(Complex(0, -1) == (Complex() -= Complex(0, 1)));
}

TEST_CASE("Complex operator-", "[complex]") {
    CHECK(Complex(-1, 2) == (Complex(0, 2) - 1));
    CHECK(Complex(1, -2) == (1 - Complex(0, 2)));
    CHECK(Complex(0, 1) == (Complex(1, 1) - Complex(1)));
    CHECK(Complex(0, -1) == (Complex() - Complex(0, 1)));
}

TEST_CASE("Complex operator*=", "[complex]") {
    CHECK(Complex(-2, 2) == (Complex(-1, 1) *= 2));
    CHECK(Complex(-2, 2) == (Complex(1, -1) *= Complex(-2)));
    CHECK(Complex(2) == (Complex(1, 1) *= conj(Complex(1, 1))));
}

TEST_CASE("Complex operator*", "[complex]") {
    CHECK(Complex(2, 4) == Complex(1, 2) * 2);
    CHECK(Complex(2, 4) == 2.0 * Complex(1, 2));
    CHECK(Complex(-4, 7) == Complex(1, 2) * Complex(2, 3));
}

TEST_CASE("Complex operator/=", "[complex]") {
    CHECK((Complex(2, 4) /= 2) == Complex(1, 2));
    CHECK((Complex(8) /= Complex(2, 3)) == Complex(16.0 / 13, -24.0 / 13));
    CHECK((Complex(8) /= Complex(2, 3)) ==
        (Complex(8) * Complex(2, -3)) / (Complex(2, 3) * Complex(2, -3)));
}

TEST_CASE("Complex operator/", "[complex]") {
    CHECK(Complex(2, 4) / 2 == Complex(1, 2));
    CHECK(8 / Complex(2, 3) == Complex(16.0 / 13, -24.0 / 13));
    CHECK(Complex(8) / Complex(2, 3) ==
        (Complex(8) * Complex(2, -3)) / (Complex(2, 3) * Complex(2, -3)));
}