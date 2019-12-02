#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <queuea/queuea.h>

TEST_CASE("ctor default" "[QueueA]") {
    QueueA q;
    CHECK(q.size() == 0);
    CHECK(q.is_empty());
    CHECK_THROWS(q.top());
}

TEST_CASE("push" "[QueueA]") {
    QueueA q;

    q.push(100);
    CHECK(q.top() == 100);
    CHECK(q.size() == 1);

    q.push(200);
    CHECK(q.top() == 100);
    CHECK(q.size() == 2);
}

TEST_CASE("pop" "[QueueA]") {
    QueueA q;
    q.push(100);
    q.push(200);
    CHECK(q.top() == 100);

    q.pop();
    CHECK(q.top() == 200);
}

TEST_CASE("ctor copy" "[QueueA]") {
    QueueA q;
    for (size_t i = 0; i < 10000; i += 100)
        q.push(float(i));

    QueueA d(q);
    CHECK(d.size() == q.size());
    while (!d.is_empty() && !q.is_empty()) {
        CHECK(q.top() == d.top());
        q.pop();
        d.pop();
    }
}

TEST_CASE("op =" "[QueueA]") {
    QueueA q;
    QueueA d;
    for (size_t i = 0; i < 10000; i += 100)
        q.push(float(i));

    d = q;
    CHECK(d.size() == q.size());
    while (!d.is_empty() && !q.is_empty()) {
        CHECK(q.top() == d.top());
        q.pop();
        d.pop();
    }
}
