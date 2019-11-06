#include <dynarray/dynarray.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.h>

namespace {

using tolstenko_l_s::DynArray;

} // namespace

TEST_CASE("DynArray creation test", "[DynArrayCreation]") {

    DynArray<int> ar;

    REQUIRE(ar.Size() == 0);
    REQUIRE(ar.Empty());
}

TEST_CASE("DynArray constructors test", "[DynArrayConstructors]") {

    DynArray<int> ar(3, 42);

    REQUIRE(!ar.Empty());
    REQUIRE(ar.Size() == 3);

    for(size_t i = 0; i < ar.Size(); ++i) {
        REQUIRE(ar[i] == 42);
    }

    for (auto value : ar) {
        REQUIRE(value == 42);
    }
}

TEST_CASE("DynArray copying test", "[DynArrayCopying]") {

    DynArray<int> ar1(3, 42);
    DynArray<int> ar2(ar1);

    REQUIRE(ar1 == ar2);
    REQUIRE(!(ar1 != ar2));

    DynArray<int> ar3;

    ar3 = ar2;
    REQUIRE(ar3 == ar1);
    REQUIRE(ar3 == ar2);
}

TEST_CASE("DynArray initializerList test", "[DynArrayInitializerList]") {

    DynArray<int> ar {0, 1, 2, 3, 4};

    REQUIRE(ar.Size() == 5);

    for(size_t i = 0; i < ar.Size(); ++i) {
        REQUIRE(ar[i] == i);
    }
}

TEST_CASE("DynArray resize test", "[DynArrayResize]") {

    DynArray<int> ar{ 0, 1, 2, 3, 4, 5, 6, 7 };

    ar.Resize(4);
    REQUIRE(ar.Size() == 4);
    REQUIRE(ar == DynArray<int> {0, 1, 2, 3});

    ar.Resize(7, 10);
    REQUIRE(ar.Size() == 7);
    REQUIRE(ar == DynArray<int> {0, 1, 2, 3, 10, 10, 10});
}

TEST_CASE("DynArray wit complex types test", "[DynArrayComplexTypes]") {

    using Strings = DynArray<std::string>;

    Strings ar{
        "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine", "ten" };

    ar.Resize(4);
    REQUIRE(ar.Size() == 4);
    REQUIRE(ar == Strings{"one", "two", "three", "four"});

    ar.Resize(7);
    REQUIRE(ar.Size() == 7);
    REQUIRE(ar == Strings{"one", "two", "three", "four", "", "", ""});

    ar.Resize(15, "ten");
    REQUIRE(ar.Size() == 15);
    REQUIRE(ar == Strings{ "one", "two", "three", "four", "", "", "",
    "ten", "ten", "ten", "ten", "ten", "ten", "ten", "ten" });
}

TEST_CASE("Two-dimensional DynArray test", "[TwoDimensional]") {

    DynArray<DynArray<int>> m {
        {1, },
        {10, 11},
        {20, 21, 22},
        {30, 31, 32, 33},
        {40, 41, 42},
        {50, 51,},
        {60},
    };
    REQUIRE(m[4] == DynArray<int>{40, 41, 42});

    m[4].Resize(5);
    REQUIRE(m[4] == DynArray<int>{40, 41, 42, 0, 0});

    m.Resize(10, {100, 200, 300});
    REQUIRE(m == DynArray<DynArray<int>>{
        {1, },
        {10, 11},
        {20, 21, 22},
        {30, 31, 32, 33},
        {40, 41, 42, 0, 0},
        {50, 51},
        {60},
        {100, 200, 300},
        {100, 200, 300},
        {100, 200, 300}
    });

}