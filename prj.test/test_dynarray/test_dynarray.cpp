#include <dynarray/dynarray.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.h>

TEST_CASE("DynArray creation test", "[DynArrayCreation]") {
    using tolstenko_l_s::DynArray;

    DynArray<int> ar;

    REQUIRE(ar.Size() == 0);
    REQUIRE(ar.Empty());
}

TEST_CASE("DynArray constructors test", "[DynArrayConstructors]") {
    using tolstenko_l_s::DynArray;

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
    using tolstenko_l_s::DynArray;

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
    using tolstenko_l_s::DynArray;

    DynArray<int> ar {0, 1, 2, 3, 4};

    REQUIRE(ar.Size() == 5);

    for(size_t i = 0; i < ar.Size(); ++i) {
        REQUIRE(ar[i] == i);
    }
}

TEST_CASE("DynArray resize test", "[DynArrayResize]") {
    using tolstenko_l_s::DynArray;

    DynArray<int> ar{ 0, 1, 2, 3, 4, 5, 6, 7 };

    ar.Resize(4);
    REQUIRE(ar.Size() == 4);
    REQUIRE(ar == DynArray<int> {0, 1, 2, 3});

    ar.Resize(7, 10);
    REQUIRE(ar.Size() == 7);
    REQUIRE(ar == DynArray<int> {0, 1, 2, 3, 10, 10, 10});
}
