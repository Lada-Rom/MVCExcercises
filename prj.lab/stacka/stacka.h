// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef STACKA_STACKA_H_20191812
#define STACKA_STACKA_H_20191812

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

//! \brief Стек значений float с реализацией на массиве.
class StackA {
public:
    StackA() = default;
    StackA(const StackA&);
    StackA& operator=(const StackA&);

    StackA(StackA&&);
    StackA& operator=(StackA&&);

    void push(const float);
    void pop();

    float& top();
    const float& top() const;

    bool is_empty() const { return !size_; }

private:
    void reserve(size_t);

    size_t size_{ 0 };
    size_t capacity_{ 0 };
    std::unique_ptr<float[]> head_;
};

#endif