#include "stackl.h"

StackL::Node::Node(const Node& rhs)
    : value(rhs.value)
    , next_(rhs.next_ ? new Node(*rhs.next_) : nullptr) {}

StackL::Node::Node(float val, Node* p)
    : value(val)
    , next_(p) {}

StackL::Node::~Node() {
    std::cout << value << std::endl;
    delete next_;
}

StackL::StackL(const StackL& rhs)
    : head_(rhs.head_ ? new Node(*rhs.head_) : nullptr) {
}

StackL& StackL::operator=(const StackL& rhs) {
    StackL temp(rhs);
    std::swap(head_, temp.head_);
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
