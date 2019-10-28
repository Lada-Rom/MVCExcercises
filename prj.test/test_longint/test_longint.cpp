
#include <sstream>
#include <longint/longint.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.h>

namespace
{

template <typename...T>
std::string makeString(const T&...t)
{
    std::ostringstream output;
    (output << ... << t);
    return output.str();
}

} // namespace

TEST_CASE("LongInt tests", "[LongInt]") {
    using tolstenko_l_s::LongInt;

    REQUIRE(makeString(LongInt(12345678)) == "12345678");
    REQUIRE(makeString(LongInt(-12345678)) == "-12345678");

    REQUIRE(LongInt(17 * 19 * 23 * 29) / 23 == 17 * 19 * 29);
    REQUIRE(LongInt(17 * 19 * 23 * 29) / -23 == -17 * 19 * 29);
    REQUIRE(LongInt(-17 * 19 * 23 * 29) / 23 == -17 * 19 * 29);
    REQUIRE(LongInt(-17 * 19 * 23 * 29) / -23 == 17 * 19 * 29);

    REQUIRE((LongInt(17 * 19 * 29) *= 23) == -17 * 19 * 23 * 29);
    REQUIRE((LongInt(17 * 19 * 29) *= -23) == -17 * 19 * 23 * 29);
    REQUIRE((LongInt(-17 * 19 * 29) *= 23) == -17 * 19 * 23 * 29);
    REQUIRE((LongInt(-17 * 19 * 29) *= -23) == 17 * 19 * 23 * 29);

    std::cout << LongInt(-3 << 24) << std::endl << std::endl;
    std::cout << (-3 << 24) << std::endl;

    LongInt l = 258;
    std::cout << l << std::endl;
    std::cout << l / -3 << std::endl << std::endl;
}
