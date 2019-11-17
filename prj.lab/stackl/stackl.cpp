#include "stackl.h"

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
