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
    st.push(1);

    CHECK(!st.is_empty());
    CHECK(st.top() == 1);
}

TEST_CASE("StackL copy", "[stackl]") {
    StackL st1;
    st1.push(2);
    StackL st2(st1);

    CHECK(st1.top() == st2.top());
}

TEST_CASE("StackL copy operator=", "[stackl]") {
    StackL st1;
    StackL st2;

    st1.push(3);
    st2 = st1;

    CHECK(st1.top() == st2.top());
}

TEST_CASE("StackL move ctor and assignment", "[stackl]") {
    StackL st1;
    st1.push(4);

    StackL st2(std::move(st1));
    CHECK(st2.top() == 4);
    CHECK(st1.is_empty());

    st1 = std::move(st2);
    CHECK(st1.top() == 4);
    CHECK(st2.is_empty());
}

TEST_CASE("StackL pop", "[stackl]") {
    StackL st1;
    CHECK_THROWS(st1.pop());

    st1.push(5);
    CHECK(st1.top() == 5);
    st1.push(6);
    CHECK(st1.top() == 6);
    st1.pop();
    CHECK(st1.top() == 5);
    st1.pop();
    CHECK(st1.is_empty());
}
