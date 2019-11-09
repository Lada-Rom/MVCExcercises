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

    iterator begin() { return data_.get(); }
    const_iterator begin() const { return data_.get(); }

    iterator end() { return data_.get() + size_; }
    const_iterator end() const { return data_.get() + size_; }

    void reserve(size_t);
    void resize(size_t, const T& = T());

    T& operator [] (size_t);
    const T& operator [] (size_t) const;

    DynArray& operator = (const DynArray&);
    DynArray& operator = (DynArray&&);

private:
    struct Deallocator{ void operator()(T* p) const { std::free(p); } };
    using StorageKeeper = std::unique_ptr<T[], Deallocator>;

    static StorageKeeper allocate(size_t);

    size_t capacity_{0};
    size_t size_{0};
    StorageKeeper data_;
};

template<typename T>
bool operator == (const DynArray<T>&, const DynArray<T>&);

template<typename T>
bool operator != (const DynArray<T>&, const DynArray<T>&);

////////////////////////////////////////////////////////////////////////////////

template<typename T>
typename DynArray<T>::StorageKeeper DynArray<T>::allocate(size_t size) {

    return StorageKeeper(static_cast<T*>(std::malloc(size * sizeof(T))));
}

template<typename T>
DynArray<T>::DynArray(size_t size, const T& value) 
    : size_(size)
    , capacity_(size)
    , data_(allocate(size)) {

    std::uninitialized_fill(begin(), end(), value);
}

template<typename T>
DynArray<T>::DynArray(const DynArray& other)
    : size_(other.size_)
    , capacity_(other.size_)
    , data_(allocate(other.size_)) {

    std::uninitialized_copy(other.begin(), other.end(), begin());
}

template<typename T>
DynArray<T>::DynArray(std::initializer_list<T> list)
    : size_(list.size())
    , capacity_(list.size())
    , data_(allocate(list.size())) {

    std::uninitialized_copy(list.begin(), list.end(), begin());
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
    std::destroy(begin(), end());
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
void DynArray<T>::reserve(size_t size) {
    if (capacity_ <= size) {
        StorageKeeper data = allocate(size);
        std::uninitialized_move(begin(), end(), data.get());
        data_ = std::move(data);
        capacity_ = size;
    }
}

template<typename T>
void DynArray<T>::resize(size_t size, const T& value) {
    reserve(size);
    if (size > size_) {
        std::uninitialized_fill(end(), begin() + size, value);
    }
    else {
        std::destroy(begin() + size, end());
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
