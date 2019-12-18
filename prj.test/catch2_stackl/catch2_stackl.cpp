#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <stackl/stackl.h>

#include <array>
#include <limits>
#include <type_traits>

TEST_CASE("StackL ctor", "[StackL]") {
    StackL s_src;
    CHECK(s_src.is_empty());
}

TEST_CASE("StackL copy ctor", "[StackL]") {
    StackL s_src;

    SECTION("Copy empty") {
        StackL s_copy(s_src);
        CHECK(s_copy.is_empty());
    }

    SECTION("Copy not empty") {
        s_src.push(1.0f);
        s_src.push(2.0f);
        s_src.push(3.0f);

        StackL s_copy(s_src);
        CHECK(!s_copy.is_empty());
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

TEST_CASE("StackL operator=", "[StackL]") {
    std::array<float, 3> data3 = { 1.0f, 2.0f, 3.0f };
    std::array<float, 5> data5 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    StackL s_3;
    // insert values to empty stack
    for (const auto value : data3) {
        s_3.push(value);
    }
    StackL s_5;
    // insert values to empty stack
    for (const auto value : data5) {
        s_5.push(value);
    }
    // create empty stack
    StackL s_empty;

    SECTION("Copy empty to itself") {
        s_empty = s_empty;
        CHECK(s_empty.is_empty());
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

TEST_CASE("StackL push", "[StackL]") {
    const int count = 3;
    float v[count] = { 1.0f, 2.0f, 3.0f };
    StackL s;
    for (int i = 0; i < count; i += 1) {
        s.push(v[i]);
        CHECK(v[i] == s.top());
        const StackL& sc(s);
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

//TEST_CASE("StackL ctor", "[stackl]") {
//    CHECK(StackL().is_empty() == true);
//    CHECK_THROWS(StackL().top() == 0);
//}
//
//TEST_CASE("StackL push", "[stackl]") {
//    StackL st;
//    st.push(1);
//
//    CHECK(!st.is_empty());
//    CHECK(st.top() == 1);
//}
//
//TEST_CASE("StackL copy", "[stackl]") {
//    StackL st1;
//    st1.push(2);
//    StackL st2(st1);
//
//    CHECK(st1.top() == st2.top());
//}
//
//TEST_CASE("StackL copy operator=", "[stackl]") {
//    StackL st1;
//    StackL st2;
//
//    st1.push(3);
//    st2 = st1;
//
//    CHECK(st1.top() == st2.top());
//}
//
//TEST_CASE("StackL move ctor and assignment", "[stackl]") {
//    StackL st1;
//    st1.push(4);
//
//    StackL st2(std::move(st1));
//    CHECK(st2.top() == 4);
//    CHECK(st1.is_empty());
//
//    st1 = std::move(st2);
//    CHECK(st1.top() == 4);
//    CHECK(st2.is_empty());
//}
//
//TEST_CASE("StackL pop", "[stackl]") {
//    StackL st1;
//    CHECK_THROWS(st1.pop());
//
//    st1.push(5);
//    CHECK(st1.top() == 5);
//    st1.push(6);
//    CHECK(st1.top() == 6);
//    st1.pop();
//    CHECK(st1.top() == 5);
//    st1.pop();
//    CHECK(st1.is_empty());
//}
