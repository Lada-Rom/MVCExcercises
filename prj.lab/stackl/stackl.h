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
    ~StackL() {delete head_;}

    StackL(StackL&&);
    StackL& operator=(StackL&&);

    void push(const float value);
    void pop();

    float& top();
    const float& top() const;

    bool is_empty() const { return !head_; }

private:
    struct Node {
        Node() = default;
        Node(const Node&);
        Node(float, Node*);
        ~Node();

        float value{0.0f};
        Node* next_{};
    };

    Node* head_{};
};

#endif