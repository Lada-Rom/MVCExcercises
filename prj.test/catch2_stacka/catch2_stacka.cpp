#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <stacka/stacka.h>

#include <array>
#include <limits>
#include <type_traits>

TEST_CASE("StackA ctor", "[StackA]") {
    StackA s_src;
    CHECK(s_src.is_empty());
}

TEST_CASE("StackA copy ctor", "[StackA]") {
    StackA s_src;

    SECTION("Copy empty") {
        StackA s_copy(s_src);
        CHECK(s_copy.is_empty());
    }

    SECTION("Copy not empty") {
        s_src.push(1.0f);
        s_src.push(2.0f);
        s_src.push(3.0f);

        StackA s_copy(s_src);
        CHECK(!s_copy.is_empty());
        CHECK(s_src.top() == s_copy.top());
        while (!s_copy.is_empty() && !s_src.is_empty()) {
            CHECK(s_src.top() == s_copy.top());
            s_src.pop();
            if (!s_src.is_empty()) {
                CHECK(s_src.top() != s_copy.top());
            }
            s_copy.pop();
            if (!s_copy.is_empty() && !s_src.is_empty()) {
                CHECK(s_src.top() == s_copy.top());
            }
        }
    }
}

TEST_CASE("StackA operator=", "[StackA]") {
    std::array<float, 3> data3 = { 1.0f, 2.0f, 3.0f };
    std::array<float, 5> data5 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    StackA s_3;
    // insert values to empty stack
    for (const auto value : data3) {
        s_3.push(value);
    }
    StackA s_5;
    // insert values to empty stack
    for (const auto value : data5) {
        s_5.push(value);
    }
    // create empty stack
    StackA s_empty;

    SECTION("Copy empty to itself") {
        s_empty = s_empty;
        CHECK(s_empty.is_empty());
        StackA s(s_empty);
        CHECK(s.is_empty());
    }

    SECTION("Copy non-empty to itself") {
        s_3 = s_3;
        CHECK(!s_3.is_empty());
        for (int i = int(data3.size()) - 1; 0 <= i; i -= 1) {
            CHECK(s_3.top() == data3[i]);
            s_3.pop();
        }
        CHECK(s_3.is_empty());
    }

    SECTION("Copy empty to non-empty") {
        s_3 = s_empty;
        CHECK(s_3.is_empty());
    }

    SECTION("Copy non-empty to empty") {
        s_empty = s_3;
        CHECK(!s_3.is_empty());
        CHECK(!s_empty.is_empty());
        while (!s_empty.is_empty() && !s_3.is_empty()) {
            CHECK(s_3.top() == s_empty.top());
            s_3.pop();
            if (!s_3.is_empty()) {
                CHECK(s_3.top() != s_empty.top());
            }
            s_empty.pop();
            if (!s_empty.is_empty() && !s_3.is_empty()) {
                CHECK(s_3.top() == s_empty.top());
            }
        }
    }

    SECTION("Copy smaller to large") {
        s_5 = s_3;
        CHECK(!s_3.is_empty());
        CHECK(!s_5.is_empty());
        while (!s_3.is_empty() && !s_5.is_empty()) {
            CHECK(s_3.top() == s_5.top());
            s_3.pop();
            if (!s_3.is_empty()) {
                CHECK(s_3.top() != s_5.top());
            }
            s_5.pop();
            if (!s_3.is_empty() && !s_5.is_empty()) {
                CHECK(s_3.top() == s_5.top());
            }
        }
        CHECK(s_3.is_empty());
        CHECK(s_5.is_empty());
    }

    SECTION("Copy larger to smaller") {
        s_3 = s_5;
        CHECK(!s_3.is_empty());
        CHECK(!s_5.is_empty());
        while (!s_3.is_empty() && !s_5.is_empty()) {
            CHECK(s_3.top() == s_5.top());
            s_3.pop();
            if (!s_3.is_empty()) {
                CHECK(s_3.top() != s_5.top());
            }
            s_5.pop();
            if (!s_3.is_empty() && !s_5.is_empty()) {
                CHECK(s_3.top() == s_5.top());
            }
        }
        CHECK(s_3.is_empty());
        CHECK(s_5.is_empty());
    }
}

TEST_CASE("StackA push", "[StackA]") {
    const int count = 3;
    float v[count] = { 1.0f, 2.0f, 3.0f };
    StackA s;
    for (int i = 0; i < count; i += 1) {
        s.push(v[i]);
        CHECK(v[i] == s.top());
        const StackA& sc(s);
        CHECK(v[i] == sc.top());
        CHECK(!s.is_empty());
        CHECK(!sc.is_empty());
    }
    s.pop();
    CHECK(v[count - 2] == s.top());
    for (int i = 0; i <= count; i += 1) {
        s.pop();
    }
    CHECK(s.is_empty());
}
