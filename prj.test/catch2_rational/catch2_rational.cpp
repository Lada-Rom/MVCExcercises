#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <rational/rational.h>

#include <array>
#include <limits>
#include <type_traits>

// before and after normalization
static std::array<const char*, 14> well_formated{
    "0/1",    "0/1",
    "13/3",   "13/3",
    "-13/3",  "-13/3",
    "0/5",    "0/1",
    "9/3",    "3/1",
    "28/2",   "14/1",
    "-28/2",  "-14/1"
};
static_assert(0 == std::tuple_size<decltype(well_formated)>::value % 2,
    "Test data array size should be even.");

static std::array<const char*, 6> bad_formated{
    "0 /1", "{2/3}", "3", "2/ 3", "13/-3", "-13/-3"
};

TEST_CASE("Rational ctor", "[rational]") {
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(3) == Rational(3, 1));
    CHECK(Rational(-3) == Rational(-3, 1));
    CHECK(Rational(10, 6) == Rational(5, 3));
    CHECK(Rational(-10, 6) == Rational(-5, 3));
    CHECK(Rational(10, -6) == Rational(-5, 3));
    CHECK(Rational(-10, -6) == Rational(5, 3));
    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("Rational operator=", "[rational]") {
}

TEST_CASE("Rational operator>> and operator<<", "[rational]") {

    for (const auto& str : well_formated) {
        std::string str_number(str);
        str_number += " ";
        CHECK_THAT(str_number,
            Catch::Matchers::Predicate<std::string>(
                [](std::string const& str) -> bool {
            std::istringstream istrm(str);
            Rational r;
            istrm >> r;
            return istrm.good();
        },
                "Good input should cause good srtream state.")
        );
    }
    for (const auto& str : well_formated) {
        CHECK_THAT(str,
            Catch::Matchers::Predicate<std::string>(
                [](std::string const& str) -> bool {
            std::istringstream istrm(str);
            Rational r;
            istrm >> r;
            return istrm.eof();
        },
                "Good input at end should cause eof srtream state.")
        );
    }
    for (const auto& str : bad_formated) {
        CHECK_THAT(str,
            Catch::Matchers::Predicate<std::string>(
                [](std::string const& str) -> bool {
            std::istringstream istrm(str);
            Rational r;
            istrm >> r;
            return istrm.fail();
        },
                "Bad input should cause fail srtream state.")
        );
    }

    using pair = std::pair<const char*, const char*>;
    for (int i = 0; i < well_formated.size() / 2; i += 1) {
        auto data = std::make_pair(well_formated[i * 2], well_formated[i * 2 + 1]);
        CHECK_THAT(data,
            Catch::Matchers::Predicate<pair>(
                [](pair const& data) -> bool {
            std::istringstream istrm(data.first);
            Rational r;
            istrm >> r;
            std::ostringstream ostrm;
            ostrm << r;
            return ostrm.str() == data.second;
        },
                "Input and output should be equal.")
        );
    }
}

TEST_CASE("Rational unary operator-", "[rational]") {
    CHECK(Rational(0) == -Rational(0));
    CHECK(Rational(3, 4) == -Rational(-3, 4));
    CHECK(Rational(3, 4) == -Rational(3, -4));
}

TEST_CASE("Rational operator+=", "[rational]") {
    CHECK((Rational(3, 4) += Rational(0)) == Rational(3, 4));
    CHECK((Rational(3, 4) += Rational(1, 4)) == Rational(1));
    CHECK((Rational(3, 4) += Rational(1, -2)) == Rational(1, 4));
    CHECK((Rational(3, 4) += Rational(3, -4)) == Rational(0));
}

TEST_CASE("Rational operator+", "[rational]") {
    CHECK((Rational(3, 4) + Rational(0)) == Rational(3, 4));
    CHECK((Rational(3, 4) + Rational(1, 4)) == Rational(1));
    CHECK((Rational(3, 4) + Rational(1, -2)) == Rational(1, 4));
    CHECK((Rational(3, 4) + Rational(3, -4)) == Rational(0));
}

TEST_CASE("Rational operator-=", "[rational]") {
    CHECK((Rational(3, 4) -= Rational(0)) == Rational(3, 4));
    CHECK((Rational(3, 4) -= Rational(3, 4)) == Rational(0));
    CHECK((Rational(3, 4) -= Rational(1, 4)) == Rational(1, 2));
    CHECK((Rational(3, 4) -= Rational(1, -4)) == Rational(1));
}

TEST_CASE("Rational operator-", "[rational]") {
    CHECK((Rational(3, 4) - Rational(0)) == Rational(3, 4));
    CHECK((Rational(3, 4) - Rational(3, 4)) == Rational(0));
    CHECK((Rational(3, 4) - Rational(1, 4)) == Rational(1, 2));
    CHECK((Rational(3, 4) - Rational(1, -4)) == Rational(1));
}

TEST_CASE("Rational operator*=", "[rational]") {
    CHECK((Rational(3, 4) *= Rational(0)) == Rational(0));
    CHECK((Rational(3, 4) *= Rational(4, 3)) == Rational(1));
    CHECK((Rational(3, 4) *= Rational(1, 2)) == Rational(3, 8));
    CHECK((Rational(3, 4) *= Rational(-1, 2)) == Rational(-3, 8));
}

TEST_CASE("Rational operator*", "[rational]") {
    CHECK((Rational(3, 4) * Rational(0)) == Rational(0));
    CHECK((Rational(3, 4) * Rational(4, 3)) == Rational(1));
    CHECK((Rational(3, 4) * Rational(1, 2)) == Rational(3, 8));
    CHECK((Rational(3, 4) * Rational(-1, 2)) == Rational(-3, 8));
}

TEST_CASE("Rational operator/=", "[rational]") {
    CHECK_THROWS(Rational(3, 4) /= Rational(0));
}

TEST_CASE("Rational operator/", "[rational]") {
    CHECK_THROWS(Rational(3, 4) / Rational(0));
}
