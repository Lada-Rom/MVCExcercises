// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef DYNARRAY_DYNARRAYT_H_20190212
#define DYNARRAY_DYNARRAYT_H_20190212

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

template<typename T>
class DynArrayT {
public:
    using iterator = T*;
    using const_iterator = const T*;

    DynArrayT() = default;
    DynArrayT(ptrdiff_t, const T& = T());
    DynArrayT(const DynArrayT& other) : DynArrayT(other, other.size()) { }
    DynArrayT(DynArrayT&& other) noexcept { swap(other); };
    DynArrayT(std::initializer_list<T> list) : DynArrayT(list, list.size()) { }

    ~DynArrayT() { std::destroy(begin(), end()); }

    ptrdiff_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    iterator begin() noexcept { return data_.get(); }
    const_iterator begin() const noexcept { return data_.get(); }

    iterator end() noexcept { return data_.get() + size_; }
    const_iterator end() const noexcept { return data_.get() + size_; }

    void reserve(ptrdiff_t);
    void resize(ptrdiff_t, const T& = T());

    void swap(DynArrayT&) noexcept;

    T& operator [] (ptrdiff_t);
    const T& operator [] (ptrdiff_t) const;

    DynArrayT& operator = (const DynArrayT&);
    DynArrayT& operator = (DynArrayT&& rhs) noexcept { swap(rhs); return *this; }

private:
    struct Deallocator{ void operator()(T* p) const { std::free(p); } };
    using StorageKeeper = std::unique_ptr<T[], Deallocator>;

    static StorageKeeper allocate(ptrdiff_t);

    template <typename Range>
    DynArrayT(const Range&, ptrdiff_t capacity);

    ptrdiff_t capacity_{0};
    ptrdiff_t size_{0};
    StorageKeeper data_;
};

template<typename T>
bool operator == (const DynArrayT<T>&, const DynArrayT<T>&);

template<typename T>
bool operator != (const DynArrayT<T>&, const DynArrayT<T>&);

////////////////////////////////////////////////////////////////////////////////

template<typename T>
typename DynArrayT<T>::StorageKeeper DynArrayT<T>::allocate(ptrdiff_t size) {
    if(size < 0)
        throw std::logic_error("Wrong size");

    return size ? StorageKeeper(static_cast<T*>(std::malloc(size * sizeof(T))))
        : StorageKeeper();
}

template<typename T>
void DynArrayT<T>::swap(DynArrayT<T>& rhs) noexcept {
    if (this != &rhs) {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(data_, rhs.data_);
    }
}

template<typename T>
DynArrayT<T>::DynArrayT(ptrdiff_t size, const T& value) 
    : size_(size)
    , capacity_(size)
    , data_(allocate(size)) {

    if (size)
        std::uninitialized_fill(begin(), end(), value);
}

template<typename T>
template <typename Range>
DynArrayT<T>::DynArrayT(const Range& range, ptrdiff_t capacity)
    : size_(std::size(range))
    , capacity_(capacity)
    , data_(allocate(capacity)) {

    assert(size_ <= capacity_);
    std::uninitialized_copy(std::begin(range), std::end(range), begin());
}

template<typename T>
T& DynArrayT<T>::operator [] (ptrdiff_t i) {
    if(i >= size_ || i < 0)
        throw std::out_of_range("Array's index is out of range");
    return data_[i];
}

template<typename T>
const T& DynArrayT<T>::operator [] (ptrdiff_t i) const {
    if (i >= size_ || i < 0)
        throw std::out_of_range("Array's index is out of range");
    return data_[i];
}

template<typename T>
DynArrayT<T>& DynArrayT<T>::operator =(const DynArrayT& other) {
    if (&other != this) {
        *this = DynArrayT(other);
    }
    return *this;
}

template<typename T>
void DynArrayT<T>::reserve(ptrdiff_t size) {
    if (capacity_ <= size) {
        *this = DynArrayT(*this, size);
    }
}

template<typename T>
void DynArrayT<T>::resize(ptrdiff_t size, const T& value) {
    reserve(size);
    if (size > size_) {
        std::uninitialized_fill(end(), begin() + size, value);
    }
    else {
        if (size < 0)
            throw std::logic_error("Wrong size");

        std::destroy(begin() + size, end());
    }
    size_ = size;
}

template<typename T>
bool operator == (const DynArrayT<T>& lhs, const DynArrayT<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (ptrdiff_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }

    return true;
}

template<typename T>
bool operator != (const DynArrayT<T>& lhs, const DynArrayT<T>& rhs) {
    return !(lhs == rhs);
}

#endif
