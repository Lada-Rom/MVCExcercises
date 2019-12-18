#include "stacka.h"

StackA::StackA(const StackA& rhs)
    : size_(rhs.size_)
    , capacity_(rhs.size_)
    , head_(std::make_unique<float[]>(rhs.size_)) {
    for(size_t i = 0; i < size_; ++i)
        head_[i] = rhs.head_[i];
}

StackA::StackA(StackA&& rhs) {
    *this = StackA(rhs);
}

void StackA::reserve(size_t size) {
    if (size > capacity_) {
        auto temp = std::make_unique<float[]>(size);
        for(size_t i = 0; i < size_; ++i)
            temp[i] = head_[i];
        std::swap(temp, head_);
        capacity_ = size;
    }
}

void StackA::push(const float value) {
    if(size_ == capacity_)
        reserve( capacity_ + 1 );
    head_[size_++] = value;
}

float& StackA::top() {
    if(size_ == 0)
        std::out_of_range("Stack is empty");
    return head_[size_ - 1];
}

const float& StackA::top() const {
    if (size_ == 0)
        std::out_of_range("Stack is empty");
    return head_[size_ - 1];
}

void StackA::pop() {
    if(size_)
        --size_;
}

StackA& StackA::operator=(StackA&& rhs) {
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
    std::swap(head_, rhs.head_);
    return *this;
}

StackA& StackA::operator=(const StackA& rhs) {
    if(&rhs != this)
        return *this = StackA(rhs);
    return *this;
}
