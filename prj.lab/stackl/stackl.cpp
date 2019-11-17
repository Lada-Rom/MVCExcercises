#include "stackl.h"

StackL::Node::Node(const Node& rhs)
    : value(rhs.value)
    , next_(rhs.next_ ? new Node(*rhs.next_) : nullptr) {}

StackL::Node::Node(float val, Node* p)
    : value(val)
    , next_(p) {}

StackL::Node::~Node() {
    delete next_;
}

StackL::StackL(const StackL& rhs)
    : head_(rhs.head_ ? new Node(*rhs.head_) : nullptr) {
}

StackL::StackL(StackL&& temp)
    : head_(temp.head_) {
    temp.head_ = nullptr;
}

StackL& StackL::operator=(StackL&& temp) {
    std::swap(head_, temp.head_);
    return *this;
}

StackL& StackL::operator=(const StackL& rhs) {
    if(&rhs != this){
        *this = StackL(rhs);
    }
    return *this;
}

float& StackL::top() {
    if (!is_empty())
        return head_->value;
    else
        throw std::logic_error("Stack is empty");
}

const float& StackL::top() const {
    if (!is_empty())
        return head_->value;
    else
        throw std::logic_error("Stack is empty");
}

void StackL::push(const float value) {
    head_ = new Node(value, head_);
}

void StackL::pop() {
    if (!is_empty())
        head_ = std::move(head_ -> next_);
    else
        throw std::logic_error("Stack is empty");
}
