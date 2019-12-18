#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <queuel/queuel.h>

TEST_CASE("ctor default" "[QueueL]") {
    QueueL q;
    CHECK(q.is_empty());
    CHECK_THROWS(q.top());
}

TEST_CASE("push" "[QueueL]") {
    QueueL q;

    q.push(100);
    CHECK(q.top() == 100);

    q.push(200);
    CHECK(q.top() == 100);
}

TEST_CASE("pop" "[QueueL]") {
    QueueL q;
    q.push(100);
    q.push(200);
    CHECK(q.top() == 100);

    q.pop();
    CHECK(q.top() == 200);
}

TEST_CASE("ctor copy" "[QueueL]") {
    QueueL q;
    for (size_t i = 0; i < 10000; i += 100)
        q.push(float(i));

    QueueL d(q);
    while (!d.is_empty() && !q.is_empty()) {
        CHECK(q.top() == d.top());
        q.pop();
        d.pop();
    }
}

TEST_CASE("op =" "[QueueL]") {
    QueueL q;
    QueueL d;
    for (size_t i = 0; i < 10000; i += 100)
        q.push(float(i));

    d = q;
    while (!d.is_empty() && !q.is_empty()) {
        CHECK(q.top() == d.top());
        q.pop();
        d.pop();
    }
}
