#include "matrixa.h"

namespace {

std::unique_ptr<float[]> allocate(
    const std::ptrdiff_t col, const std::ptrdiff_t row) {

    //MatrixA(0, 0) is allowed
    if (col < 0 || row < 0 || ((col == 0) != (row == 0)))
        throw std::invalid_argument("Wrong size");

    return std::unique_ptr<float[]>(new float[col * row]);
}

} // namespace

void MatrixA::swap(MatrixA& rhs) {
    if (this != &rhs) {
        std::swap(n_row_, rhs.n_row_);
        std::swap(n_col_, rhs.n_col_);
        std::swap(data_, rhs.data_);
    }
}

MatrixA::MatrixA(const MatrixA& rhs)
    : n_col_(rhs.col_count())
    , n_row_(rhs.row_count())
    , data_(allocate(rhs.col_count(), rhs.row_count())) {

    const auto begin = rhs.data_.get();
    const auto end = begin + n_row_ * n_col_;
    std::copy(begin, end, data_.get());
}

MatrixA::MatrixA(const std::ptrdiff_t col, const std::ptrdiff_t row)
    : n_col_(col)
    , n_row_(row)
    , data_(allocate(col, row)) {}
