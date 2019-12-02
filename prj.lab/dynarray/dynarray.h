// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#ifndef DYNARRAY_DYNARRAY_H_20190611
#define DYNARRAY_DYNARRAY_H_20190611

namespace tolstenko_l_s {

class DynArray {
public:
    DynArray() = default;
    DynArray(const DynArray&);
    DynArray(const size_t);
    ~DynArray() { delete[] data_; }

    DynArray& operator = (const DynArray&);

    DynArray(DynArray&&);
    DynArray& operator = (DynArray&&);

    float& operator [] (const size_t);
    const float& operator [] (const size_t) const;

    size_t size() const { return size_; }
    bool empty() const { return !size_; }

    void resize(const size_t);
    void reserve(const size_t);

private:
    void check_range(size_t) const;

    size_t capacity_{};
    size_t size_{};
    float* data_{ nullptr };
};

} //namespace tolstenko_l_s

using tolstenko_l_s::DynArray;

#endif
