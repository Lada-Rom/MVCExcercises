#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <matrixa/matrixa.h>

TEST_CASE("MatrixA ctor", "[matrixa]") {
    MatrixA m_empty;
    CHECK(0 == m_empty.col_count());
    CHECK(0 == m_empty.row_count());
    CHECK_THROWS(MatrixA(-1, 3));
    CHECK_THROWS(MatrixA(1, -3));
    CHECK_THROWS(MatrixA(0, 3));
    CHECK_THROWS(MatrixA(1, 0));

    MatrixA m3x4(4, 3);
//    CHECK(4 == m3x4.col_count());
//    CHECK(3 == m3x4.row_count());
//    for (std::ptrdiff_t i_row(0); i_row < m3x4.row_count(); i_row += 1) {
//        for (std::ptrdiff_t i_col(0); i_col < m3x4.col_count(); i_col += 1) {
//            CHECK(m3x4.at(i_row, i_col) == Approx(0.0f));
//        }
//    }
}

//TEST_CASE("MatrixA copy ctor", "[matrixa]") {
//}
//
//TEST_CASE("MatrixA operator=", "[matrixa]") {
//}
//
//TEST_CASE("MatrixA operator[]", "[matrixa]") {
//    MatrixA m3x4(4, 3);
//    for (std::ptrdiff_t i_row(0); i_row < m3x4.row_count(); i_row += 1) {
//        for (std::ptrdiff_t i_col(0); i_col < m3x4.col_count(); i_col += 1) {
//            CHECK_NOTHROW(m3x4.at(i_row, i_col));
//            m3x4.at(i_row, i_col) = (i_row + 1) * (i_col + 1);
//            CHECK_THROWS(m3x4.at(-1, i_col));
//            CHECK_THROWS(m3x4.at(m3x4.row_count(), i_col));
//        }
//        CHECK_THROWS(m3x4.at(i_row, -1));
//        CHECK_THROWS(m3x4.at(i_row, m3x4.col_count()));
//    }
//    const MatrixA& cm(m3x4);
//    for (std::ptrdiff_t i_row(0); i_row < cm.row_count(); i_row += 1) {
//        for (std::ptrdiff_t i_col(0); i_col < cm.col_count(); i_col += 1) {
//            CHECK_NOTHROW(cm.at(i_row, i_col));
//            CHECK(cm.at(i_row, i_col) == Approx((i_row + 1) * (i_col + 1)));
//            CHECK_THROWS(cm.at(-1, i_col));
//            CHECK_THROWS(cm.at(m3x4.row_count(), i_col));
//        }
//        CHECK_THROWS(cm.at(i_row, -1));
//        CHECK_THROWS(cm.at(i_row, m3x4.col_count()));
//    }
//}
