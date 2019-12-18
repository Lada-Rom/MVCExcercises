#include "queuel.h"
#include <stdexcept>
#include <algorithm>

QueueL::Node::Node(const Node& rhs)
    : value_(rhs.value_)
    , next_(rhs.next_ ? new Node(*rhs.next_) : nullptr) {
}

QueueL::Node::Node(float v, Node* p)
    : value_(v)
    , next_(p) {
}

QueueL::Node::~Node() {
    delete next_;
}

QueueL::~QueueL() {
    delete head_;
}

float& QueueL::top() {
    if(is_empty())
        throw std::logic_error("Empty queue");
    return head_->value_;
}

const float& QueueL::top() const {
    if (is_empty())
        throw std::logic_error("Empty queue");
    return head_->value_;
}

void QueueL::push(const float v) {
    if (!is_empty()) {
        tail_ ->next_ = new Node(v);
        tail_ = tail_ ->next_;
    }
    else {
        head_ = tail_ = new Node(v);
    }
}

void QueueL::pop() {
    if (head_) {
        Node* temp = head_;
        head_ = head_ ->next_;
        temp ->next_ = nullptr;
        delete temp;
    }
}

QueueL::QueueL(const QueueL& rhs)
    : head_(rhs.head_ ? new Node(*rhs.head_) : nullptr) {
}

QueueL& QueueL::operator=(QueueL&& rhs) {
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    return *this;
}

QueueL& QueueL::operator=(const QueueL& rhs) {
    if(this != &rhs)
        return *this = QueueL(rhs);
    return *this;
}

QueueL::QueueL(QueueL&& rhs)
    : head_(rhs.head_)
    , tail_(rhs.tail_) {
    rhs.head_ = rhs.tail_ = nullptr;
}
