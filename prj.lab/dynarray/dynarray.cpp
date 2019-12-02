#include "dynarray.h"
#include <stdexcept>
#include <string>

DynArray::DynArray(const size_t s)
    : capacity_(s)
    , size_(s)
    , data_(new float[s]{}) {
}

void DynArray::check_range(size_t s) const {
    if(s >= size_)
        throw std::out_of_range("Index is out of range " + std::to_string(s));
}

float& DynArray::operator [] (const size_t s) {
    check_range(s);
    return data_[s];
}

const float& DynArray::operator [] (const size_t s) const {
    check_range(s);
    return data_[s];
}

DynArray::DynArray(DynArray&& rhs)
    : capacity_(rhs.capacity_)
    , size_(rhs.size_) {
    std::swap(rhs.data_, data_);
}

DynArray& DynArray::operator = (DynArray&& rhs) {
    std::swap(rhs.capacity_, capacity_);
    std::swap(rhs.size_, size_);
    std::swap(rhs.data_, data_);
    return *this;
}

DynArray::DynArray(const DynArray& rhs)
    : capacity_(rhs.size_)
    , size_(rhs.size_)
    , data_(new float[rhs.size_]) {
    for(size_t i = 0; i < size_; ++i)
        data_[i] = rhs.data_[i];
}

DynArray& DynArray::operator = (const DynArray& rhs) {
    if(this != &rhs)
        *this = DynArray(rhs);
    return *this;
}

void DynArray::reserve(const size_t s) {
    if (capacity_ < s) {
        DynArray temp;
        temp.capacity_ = s;
        temp.size_ = size_;
        temp.data_ = new float[s];

        for(size_t i = 0; i < size_; ++i)
            temp.data_[i] = data_[i];
        *this = std::move(temp);
    }
}

void DynArray::resize(const size_t s) {
    reserve(s);
    for(size_t i = size_; i < s; ++i)
        data_[i] = 0.0f;
    size_ = s;
}
