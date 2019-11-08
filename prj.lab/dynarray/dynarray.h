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

    ~DynArray();

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    void resize (size_t, const T& = T());

    T& operator [] (size_t);
    const T& operator [] (size_t) const;

    DynArray& operator = (const DynArray&);
    DynArray& operator = (DynArray&&);

private:
    static T* allocate(size_t);
    void construct_fill(const T&, size_t);
    void construct_copy(const T* begin, const T* end);
    void construct_move(T* begin, T* end);
    void destroy(size_t);

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
T* DynArray<T>::allocate(size_t size) {

    return static_cast<T*>(std::malloc(size * sizeof(T)));
}

template<typename T>
void DynArray<T>::construct_fill(const T& value, size_t count) {

    assert(size_ + count <= capacity_);

    for (; count; --count) {
        new(end()) T(value);
        ++size_;
    }
}

template<typename T>
void DynArray<T>::construct_copy(const T* inputBegin, const T* inputEnd) {

    for (const T* p = inputBegin; p != inputEnd; ++p) {
        assert(size_ < capacity_);
        new(end()) T(*p);
        ++size_;
    }
}

template<typename T>
void DynArray<T>::construct_move(T* inputBegin, T* inputEnd) {

    for (T* p = inputBegin; p != inputEnd; ++p) {
        assert(size_ < capacity_);
        new(end()) T(std::move(*p));
        ++size_;
    }
}

template<typename T>
void DynArray<T>::destroy(size_t count) {
    assert(count <= size_);
    for (; count; --count) {
        (end() - 1)->~T();
        --size_;
    }
}

template<typename T>
DynArray<T>::DynArray(size_t size, const T& value) 
    : capacity_(size)
    , data_(allocate(size)) {

    try {
        construct_fill(value, size);
    } catch (...) {
        DynArray::~DynArray();
        throw;
    }
}

template<typename T>
DynArray<T>::DynArray(const DynArray& other)
    : capacity_(other.size_)
    , data_(allocate(other.size_)) {

    try {
        construct_copy(other.begin(), other.end());
    }
    catch (...) {
        DynArray::~DynArray();
        throw;
    }
}

template<typename T>
DynArray<T>::DynArray(std::initializer_list<T> list)
    : capacity_(list.size())
    , data_(allocate(list.size())) {

    try {
        construct_copy(list.begin(), list.end());
    }
    catch (...) {
        DynArray::~DynArray();
        throw;
    }
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
DynArray<T>::~DynArray() {
    destroy(size_);
    std::free(data_);
}

template<typename T>
T& DynArray<T>::operator [] (size_t i) {
    if(i >= size_)
        throw std::out_of_range("Array's index is out of range");
    return data_[i];
}

template<typename T>
const T& DynArray<T>::operator [] (size_t i) const {
    if (i >= size_)
        throw std::out_of_range("Array's index is out of range");
    return data_[i];
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
void DynArray<T>::resize(size_t size, const T& value) {
    if(capacity_ <= size) {
        DynArray t;
        t.data_ = allocate(size);
        t.capacity_ = size;
        t.construct_move(begin(), end());
        t.size_ = size_;
        operator=(std::move(t));
    }
    if (size > size_) {
        construct_fill(value, size - size_);
    }
    else {
        destroy(size_ - size);
    }
    size_ = size;
}

template<typename T>
bool operator == (const DynArray<T>& lhs, const DynArray<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (size_t i = 0; i < lhs.size(); ++i) {
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

using DynArray = tolstenko_l_s::DynArray<float>;

#endif
