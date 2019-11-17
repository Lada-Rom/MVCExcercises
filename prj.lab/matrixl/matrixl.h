// Copyright 2019 by Tolstenko Lada under Free Public License 1.0.0

#pragma once
#ifndef MATRIXL_MATRIXL_H_20191711
#define MATRIXL_MATRIXL_H_20191711

#include <cstddef>
#include <stdexcept>
#include <memory>

class MatrixL {
public:
    MatrixL() = default;
    MatrixL(const MatrixL&);
    MatrixL(const std::ptrdiff_t, const std::ptrdiff_t);
    ~MatrixL() = default;
    MatrixL& operator=(const MatrixL&);

    //MatrixL(MatrixL&&) = default;
    //MatrixL& operator=(MatrixL&&) = default;

    std::ptrdiff_t row_count() const { return n_row_; }
    std::ptrdiff_t col_count() const { return n_col_; }

    void swap(MatrixL&);

    float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i);
    const float& at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const;
private:
    size_t n_row_{ 0 };
    size_t n_col_{ 0 };
    std::unique_ptr<float[]> data_;
};

inline void swap(MatrixL& lhs, MatrixL& rhs) { lhs.swap(rhs); }

#endif
