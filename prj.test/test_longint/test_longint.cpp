
#include <sstream>
#include <longint/longint.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.h>

TEST_CASE("LongInt tests", "[LongInt]") {
    using tolstenko_l_s::LongInt;

    REQUIRE(LongInt(12345678) == 12345678);
    REQUIRE(LongInt(-12345678) == -12345678);

    REQUIRE(LongInt(17 * 19 * 23 * 29) / 23 == 17 * 19 * 29);
    REQUIRE(LongInt(17 * 19 * 23 * 29) / -23 == -17 * 19 * 29);
    REQUIRE(LongInt(-17 * 19 * 23 * 29) / 23 == -17 * 19 * 29);
    REQUIRE(LongInt(-17 * 19 * 23 * 29) / -23 == 17 * 19 * 29);

    REQUIRE((LongInt(17 * 19 * 29) *= 23) == 17 * 19 * 23 * 29);
    REQUIRE((LongInt(17 * 19 * 29) *= -23) == -17 * 19 * 23 * 29);
    REQUIRE((LongInt(-17 * 19 * 29) *= 23) == -17 * 19 * 23 * 29);
    REQUIRE((LongInt(-17 * 19 * 29) *= -23) == 17 * 19 * 23 * 29);
}
