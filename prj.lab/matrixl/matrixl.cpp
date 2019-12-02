#include "matrixl.h"

namespace {
using Row = std::unique_ptr<float[]>;

std::unique_ptr<Row[]> make_data(
    const std::ptrdiff_t col, const std::ptrdiff_t row) {

    //MatrixL(0, 0) is allowed
    if (row < 0 || ((col == 0) != (row == 0)))
        throw std::invalid_argument("Wrong size");

    auto data = std::make_unique<Row[]>(row);
    for(ptrdiff_t i = 0; i < row; ++i)
        data[i] = std::make_unique<float[]>(col);

    return data;
}

} // namespace

MatrixL::MatrixL(const MatrixL& rhs)
    : n_col_(rhs.col_count())
    , n_row_(rhs.row_count())
    , data_(make_data(rhs.col_count(), rhs.row_count())) {

    for(ptrdiff_t i = 0; i < rhs.n_row_; ++i)
        for (ptrdiff_t j = 0; j < rhs.n_row_; ++j)
            data_[i][j] = rhs.data_[i][j];
}

void MatrixL::check_range(
    const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
    if (row_i < 0 || col_i < 0 || row_i == row_count() || col_i == col_count())
        throw std::out_of_range("Index is out of range");
}

MatrixL& MatrixL::operator=(const MatrixL& rhs) {
    return *this = MatrixL(rhs);
}

MatrixL::MatrixL(const std::ptrdiff_t col, const std::ptrdiff_t row)
    : n_col_(col)
    , n_row_(row)
    , data_(make_data(col, row)) {}

float& MatrixL::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
    check_range(row_i, col_i);
    return data_[row_i][col_i];
}

const float& MatrixL::at(
    const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
    check_range(row_i, col_i);
    return data_[row_i][col_i];
}
