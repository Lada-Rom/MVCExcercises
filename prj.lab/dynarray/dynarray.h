// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef DYNARRAY_DYNARRAY_H_20190611
#define DYNARRAY_DYNARRAY_H_20190611

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace tolstenko_l_s {

template<typename T>
class DynArray {
public:
    using iterator = T*;
    using const_iterator = const T*;

    DynArray() = default;
    DynArray(size_t, const T& = T());
    DynArray(const DynArray&);
    DynArray(DynArray&&);
    DynArray(std::initializer_list<T>);

    ~DynArray() { delete [] data_; }

    size_t Size() const { return size_; }
    bool Empty() const { return size_ == 0; }

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    void Resize (size_t, const T& = T());

    T& operator [] (size_t i) { return data_[i]; }
    const T& operator [] (size_t i) const { return data_[i]; }

    DynArray& operator = (const DynArray&);
    DynArray& operator = (DynArray&&);

private:
    size_t capacity_{0};
    size_t size_{0};
    T* data_{nullptr};
};

template<typename T>
bool operator == (const DynArray<T>&, const DynArray<T>&);

template<typename T>
bool operator != (const DynArray<T>&, const DynArray<T>&);

////////////////////////////////////////////////////////////////////////////////

template<typename T>
DynArray<T>::DynArray(size_t size, const T& value) 
    : size_(size)
    , capacity_(size)
    , data_(new T[size]) {

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

template<typename T>
DynArray<T>::DynArray(const DynArray& other)
    : size_(other.size_)
    , capacity_(other.size_)
    , data_(new T[other.size_]) {

    std::copy(other.begin(), other.end(), data_);
}

template<typename T>
DynArray<T>::DynArray(DynArray&& other)
    : size_(other.size_)
    , capacity_(other.size_)
    , data_(other.data_) {

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template<typename T>
DynArray<T>::DynArray(std::initializer_list<T> list)
    : size_(list.size())
    , capacity_(list.size())
    , data_(new T[list.size()]) {

    std::copy(list.begin(), list.end(), data_);
}

template<typename T>
DynArray<T>& DynArray<T>::operator =(const DynArray& other) {
    if (&other != this) {
        *this = DynArray(other);
    }
    return *this;
}

template<typename T>
DynArray<T>& DynArray<T>::operator =(DynArray&& other) {
    if (&other != this) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }
    return *this;
}

template<typename T>
void DynArray<T>::Resize(size_t size, const T& value) {
    if(capacity_ <= size) {
        DynArray t(size, value);
        std::copy(begin(), end(), t.data_);
        operator = (std::move(t));
    }
    else if(size > size_) {
        std::fill(data_ + size_, data_ + size, value);
    }
    size_ = size;
}

template<typename T>
bool operator == (const DynArray<T>& lhs, const DynArray<T>& rhs) {
    if (lhs.Size() != rhs.Size())
        return false;

    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }

    return true;
}

template<typename T>
bool operator != (const DynArray<T>& lhs, const DynArray<T>& rhs) {
    return !(lhs == rhs);
}

} //namespace tolstenko_l_s

#endif
