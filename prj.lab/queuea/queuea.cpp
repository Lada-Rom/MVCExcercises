#include "queuea.h"
#include <stdexcept>
#include <algorithm>

QueueA::QueueA(const QueueA& rhs)
    : capacity_(rhs.size_)
    , size_(rhs.size_)
    , data_(std::make_unique<float[]>(rhs.size_)) {
    for (size_t i = 0; i < size_; ++i)
        data_[i] = rhs.data_[(i + rhs.iHead_) % rhs.capacity_];
}

QueueA& QueueA::operator=(const QueueA& rhs) {
    return *this = QueueA(rhs);
}

float& QueueA::top() {
    if(size_)
        return data_[iHead_];
    else
        throw std::logic_error("Empty queue");
}

const float& QueueA::top() const {
    if (size_)
        return data_[iHead_];
    else
        throw std::logic_error("Empty queue");
}

void QueueA::push(const float value) {
    if(size_ == capacity_)
        reserve(std::max<size_t>(capacity_ * 2, 1));
    data_[iHead_ + size_++] = value;
}

void QueueA::reserve(size_t s) {
    if (s > capacity_) {
        auto buf = std::make_unique<float[]>(s);
        for(size_t i = 0; i < size_; ++i)
            buf[i] = data_[(i + iHead_) % capacity_];
        std::swap(buf, data_);
        capacity_ = s;
        iHead_ = 0;
    }
}

void QueueA::pop() {
    if(!size_)
        throw std::logic_error("Queue is empty");
    iHead_ = (iHead_ + 1) % capacity_;
    --size_;
}
