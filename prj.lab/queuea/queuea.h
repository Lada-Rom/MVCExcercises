// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#pragma once
#ifndef QUEUEA_QUEUEA_H
#define QUEUEA_QUEUEA_H

#include <memory>

//! \brief Очередь значений float с реализацией на массиве (подвижные концы).
class QueueA {
public:
    QueueA() = default;
    QueueA(const QueueA&);
    QueueA& operator=(const QueueA&);
    ~QueueA() = default;

    QueueA(QueueA&&) = default;
    QueueA& operator=(QueueA&&) = default;

    void push(const float);
    void pop();

    float& top();
    const float& top() const;

    const size_t size() const { return size_; }
    bool is_empty() const { return (!size_); }

private:
    void reserve(size_t);

    size_t iHead_{};
    size_t size_{};
    size_t capacity_{};
    std::unique_ptr<float[]> data_;
};

#endif
