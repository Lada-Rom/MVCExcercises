// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#pragma once
#ifndef MATRIXA_MATRIXA_H_20191011
#define MATRIXA_MATRIXA_H_20191011

#include <cstddef>
#include <stdexcept>
#include <memory>

class MatrixA {
public:
    MatrixA() = default;
    MatrixA(const MatrixA&);
    MatrixA(const std::ptrdiff_t, const std::ptrdiff_t);
    ~MatrixA() = default;
    MatrixA& operator=(const MatrixA&);

    //MatrixA(MatrixA&&) = default;
    //MatrixA& operator=(MatrixA&&) = default;

    std::ptrdiff_t row_count() const { return n_row_; }
    std::ptrdiff_t col_count() const { return n_col_; }

    void swap(MatrixA&);

    float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i);
    const float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const;
private:
    size_t n_row_{ 0 };
    size_t n_col_{ 0 };
    std::unique_ptr<float[]> data_;
};

inline void swap(MatrixA& lhs, MatrixA& rhs) { lhs.swap(rhs); }

#endif
