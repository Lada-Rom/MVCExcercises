// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef STACKL_STACKL_H_20191711
#define STACKL_STACKL_H_20191711

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

//! \brief Стек значений float с реализацией на списке.
class StackL {
public:
    StackL() = default;
    StackL(const StackL&);
    StackL& operator=(const StackL&);

    void push(const float value);
    void pop();

    float& top();
    const float& top() const;

    bool is_empty() const { return !head_; }
private:

    struct Node {
        Node() = default;
        Node(float val, std::unique_ptr<Node> p) 
            : value(val)
            , next_(std::move(p)) {}

        float value{0.0f};
        std::unique_ptr<Node> next_;
    };

    std::unique_ptr<Node> head_;
};

#endif