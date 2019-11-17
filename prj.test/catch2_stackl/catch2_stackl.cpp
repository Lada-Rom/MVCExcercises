#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <stackl/stackl.h>

#include <array>
#include <limits>
#include <type_traits>

TEST_CASE("StackL ctor", "[stackl]") {
    CHECK(StackL().is_empty() == true);
    CHECK_THROWS(StackL().top() == 0);
}

TEST_CASE("StackL push", "[stackl]") {
    StackL st;
    st.push(2);

    CHECK(!st.is_empty());
    CHECK(st.top() == 2);
}

// before and after normalization
//static std::array<const char*, 14> well_formated{
//    "0/1",    "0/1",
//    "13/3",   "13/3",
//    "-13/3",  "-13/3",
//    "0/5",    "0/1",
//    "9/3",    "3/1",
//    "28/2",   "14/1",
//    "-28/2",  "-14/1"
//};
//static_assert(0 == std::tuple_size<decltype(well_formated)>::value % 2,
//    "Test data array size should be even.");
//
//static std::array<const char*, 6> bad_formated{
//    "0 /1", "{2/3}", "3", "2/ 3", "13/-3", "-13/-3"
//};
//
//TEST_CASE("StackL ctor", "[stackl]") {
//    CHECK(StackL() == StackL(0, 1));
//    CHECK(StackL(3) == StackL(3, 1));
//    CHECK(StackL(-3) == StackL(-3, 1));
//    CHECK(StackL(10, 6) == StackL(5, 3));
//    CHECK(StackL(-10, 6) == StackL(-5, 3));
//    CHECK(StackL(10, -6) == StackL(-5, 3));
//    CHECK(StackL(-10, -6) == StackL(5, 3));
//    CHECK_THROWS(StackL(1, 0));
//}
//
//TEST_CASE("StackL operator=", "[stackl]") {
//}
//
//TEST_CASE("StackL operator>> and operator<<", "[stackl]") {
//
//    for (const auto& str : well_formated) {
//        std::string str_number(str);
//        str_number += " ";
//        CHECK_THAT(str_number,
//            Catch::Matchers::Predicate<std::string>(
//                [](std::string const& str) -> bool {
//            std::istringstream istrm(str);
//            StackL r;
//            istrm >> r;
//            return istrm.good();
//        },
//                "Good input should cause good srtream state.")
//        );
//    }
//    for (const auto& str : well_formated) {
//        CHECK_THAT(str,
//            Catch::Matchers::Predicate<std::string>(
//                [](std::string const& str) -> bool {
//            std::istringstream istrm(str);
//            StackL r;
//            istrm >> r;
//            return istrm.eof();
//        },
//                "Good input at end should cause eof srtream state.")
//        );
//    }
//    for (const auto& str : bad_formated) {
//        CHECK_THAT(str,
//            Catch::Matchers::Predicate<std::string>(
//                [](std::string const& str) -> bool {
//            std::istringstream istrm(str);
//            StackL r;
//            istrm >> r;
//            return istrm.fail();
//        },
//                "Bad input should cause fail srtream state.")
//        );
//    }
//
//    using pair = std::pair<const char*, const char*>;
//    for (int i = 0; i < well_formated.size() / 2; i += 1) {
//        auto data = std::make_pair(well_formated[i * 2], well_formated[i * 2 + 1]);
//        CHECK_THAT(data,
//            Catch::Matchers::Predicate<pair>(
//                [](pair const& data) -> bool {
//            std::istringstream istrm(data.first);
//            StackL r;
//            istrm >> r;
//            std::ostringstream ostrm;
//            ostrm << r;
//            return ostrm.str() == data.second;
//        },
//                "Input and output should be equal.")
//        );
//    }
//}
//
//TEST_CASE("StackL unary operator-", "[stackl]") {
//    CHECK(StackL(0) == -StackL(0));
//    CHECK(StackL(3, 4) == -StackL(-3, 4));
//    CHECK(StackL(3, 4) == -StackL(3, -4));
//}
//
//TEST_CASE("StackL operator+=", "[stackl]") {
//    CHECK((StackL(3, 4) += StackL(0)) == StackL(3, 4));
//    CHECK((StackL(3, 4) += StackL(1, 4)) == StackL(1));
//    CHECK((StackL(3, 4) += StackL(1, -2)) == StackL(1, 4));
//    CHECK((StackL(3, 4) += StackL(3, -4)) == StackL(0));
//}
//
//TEST_CASE("StackL operator+", "[stackl]") {
//    CHECK((StackL(3, 4) + StackL(0)) == StackL(3, 4));
//    CHECK((StackL(3, 4) + StackL(1, 4)) == StackL(1));
//    CHECK((StackL(3, 4) + StackL(1, -2)) == StackL(1, 4));
//    CHECK((StackL(3, 4) + StackL(3, -4)) == StackL(0));
//}
//
//TEST_CASE("StackL operator-=", "[stackl]") {
//    CHECK((StackL(3, 4) -= StackL(0)) == StackL(3, 4));
//    CHECK((StackL(3, 4) -= StackL(3, 4)) == StackL(0));
//    CHECK((StackL(3, 4) -= StackL(1, 4)) == StackL(1, 2));
//    CHECK((StackL(3, 4) -= StackL(1, -4)) == StackL(1));
//}
//
//TEST_CASE("StackL operator-", "[stackl]") {
//    CHECK((StackL(3, 4) - StackL(0)) == StackL(3, 4));
//    CHECK((StackL(3, 4) - StackL(3, 4)) == StackL(0));
//    CHECK((StackL(3, 4) - StackL(1, 4)) == StackL(1, 2));
//    CHECK((StackL(3, 4) - StackL(1, -4)) == StackL(1));
//}
//
//TEST_CASE("StackL operator*=", "[stackl]") {
//    CHECK((StackL(3, 4) *= StackL(0)) == StackL(0));
//    CHECK((StackL(3, 4) *= StackL(4, 3)) == StackL(1));
//    CHECK((StackL(3, 4) *= StackL(1, 2)) == StackL(3, 8));
//    CHECK((StackL(3, 4) *= StackL(-1, 2)) == StackL(-3, 8));
//}
//
//TEST_CASE("StackL operator*", "[stackl]") {
//    CHECK((StackL(3, 4) * StackL(0)) == StackL(0));
//    CHECK((StackL(3, 4) * StackL(4, 3)) == StackL(1));
//    CHECK((StackL(3, 4) * StackL(1, 2)) == StackL(3, 8));
//    CHECK((StackL(3, 4) * StackL(-1, 2)) == StackL(-3, 8));
//}
//
//TEST_CASE("StackL operator/=", "[stackl]") {
//    CHECK_THROWS(StackL(3, 4) /= StackL(0));
//}
//
//TEST_CASE("StackL operator/", "[stackl]") {
//    CHECK_THROWS(StackL(3, 4) / StackL(0));
//}
