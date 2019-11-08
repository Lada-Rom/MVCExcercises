
#include <sstream>
#include <longint/longint.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("LongInt tests", "[LongInt]") {
    using tolstenko_l_s::LongInt;

    CHECK(LongInt(12345678) == 12345678);
    CHECK(LongInt(-12345678) == -12345678);

    CHECK(LongInt(17 * 19 * 23 * 29) / 23 == 17 * 19 * 29);
    CHECK(LongInt(17 * 19 * 23 * 29) / -23 == -17 * 19 * 29);
    CHECK(LongInt(-17 * 19 * 23 * 29) / 23 == -17 * 19 * 29);
    CHECK(LongInt(-17 * 19 * 23 * 29) / -23 == 17 * 19 * 29);

    CHECK((LongInt(17 * 19 * 29) *= 23) == 17 * 19 * 23 * 29);
    CHECK((LongInt(17 * 19 * 29) *= -23) == -17 * 19 * 23 * 29);
    CHECK((LongInt(-17 * 19 * 29) *= 23) == -17 * 19 * 23 * 29);
    CHECK((LongInt(-17 * 19 * 29) *= -23) == 17 * 19 * 23 * 29);
}
