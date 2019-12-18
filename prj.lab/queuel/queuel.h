// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#pragma once
#ifndef QUEUEL_QUEUEL_H_20191812
#define QUEUEL_QUEUEL_H_20191812

#include <memory>

//! \brief Очередь значений float с реализацией на массиве (подвижные концы).
class QueueL {
public:
    QueueL() = default;
    QueueL(const QueueL&);
    QueueL& operator=(const QueueL&);
    ~QueueL();

    QueueL(QueueL&&);
    QueueL& operator=(QueueL&&);

    void push(const float);
    void pop();

    float& top();
    const float& top() const;

    bool is_empty() const { return (!head_); }

private:
    struct Node {
        Node() = default;
        Node(const Node&);
        explicit Node(float, Node* = nullptr);
        ~Node();

        float value_{ 0 };
        Node* next_{};
    };

    Node* head_{};
    Node* tail_{};
};

#endif
