// math0520lib
// https://github.com/zachMahan64/math0520lib
// 2025
// Created by Zach Mahan

#ifndef MATH0520LIB_MAT_HPP
#define MATH0520LIB_MAT_HPP
#include "vec_operations.hpp"
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace m52l {

/**
 * simple matrix class supporting basic row operations
 *
 * supports all standard numeric types via templates
 *
 * interally composed of an std::array of rows, where each row is a vector (for
 * easy row swapping)
 *
 * template params: H (height). W (width). T (numeric type)
 */
template <size_t H, size_t W, typename T>
    requires std::is_integral_v<T> || std::is_floating_point_v<T>
class Mat {
  private:
    std::array<std::vector<T>, H> rows{};
    int print_precision = 2; // default to 2

  public:
    Mat() {
        // zero init
        for (auto& row : rows) {
            row = std::vector<T>(W);
        }
    }

    Mat(const std::initializer_list<std::initializer_list<T>>& lists) {
        if (lists.size() != H) {
            throw std::runtime_error(
                "invalid row length when constructing Mat");
        }
        size_t i = 0;
        for (const auto& list : lists) {
            if (list.size() != W) {
                throw std::runtime_error(
                    "invalid column length when constructing Mat");
            }

            rows[i] = std::vector<T>(list.begin(), list.end());
            i++;
        }
    }

    // get the value of entry located at the zero-indexed entry given by (row,
    // col)
    T at(size_t row, size_t col) {
        if (row >= H || col >= W) {
            throw std::out_of_range(
                "out of bounds reading matrix entry: Mat::at");
        }
        return rows.at(row).at(col);
    }

    // swap specified zero-indexed rows (a, b)
    void swap_rows(size_t a, size_t b) {
        if (a >= H || b >= H) {
            throw std::out_of_range(
                "out of bounds reading matrix entry: Mat::swap_rows");
        }
        std::vector<T> temp = std::move(rows.at(b));
        rows.at(b) = std::move(rows.at(a));
        rows.at(a) = std::move(temp);
    }

    // swap specified zero-indexed rows with scalars (a, a_scalar, b, b_scalar)
    void swap_rows(size_t a, T a_scalar, size_t b, T b_scalar) {
        if (a >= H || b >= H) {
            throw std::out_of_range(
                "out of bounds reading matrix entry: Mat::swap_rows");
        }
        // scale a (before swap)
        scale(rows.at(a), a_scalar);
        // scale b in a temp
        std::vector<T> temp_b = std::move(rows.at(b));
        scale(temp_b, b_scalar);
        // swap
        rows.at(b) = std::move(rows.at(a));
        rows.at(a) = std::move(temp_b);
    }

    // copy a row to the first paramter, from the second paramter
    //
    // each paramter should reference a zero-indexed row
    void row_into_from(size_t into, size_t from) {
        if (from >= H || into >= H) {
            throw std::out_of_range(
                "out of bounds reading matrix entry: Mat::copy_row");
        }
        rows.at(into) = rows.at(from);
    }

    // copy a row to the first paramter, from the second paramter with a scalar
    // applied
    //
    // each paramter should reference a zero-indexed row
    void row_into_from(size_t into, size_t from, T scalar) {
        if (from >= H || into >= H) {
            throw std::out_of_range(
                "out of bounds reading matrix entry: Mat::copy_row");
        }
        auto temp = rows.at(from);
        scale(temp, scalar);
        rows.at(into) = std::move(temp);
    }

    /**
     * set a row to the sum of two other rows in the matrix, all zero-indexed
     * paramters: (dest, src_a, src_b) where R_dest <== R_src_a + R_src_b
     */
    void set_row_to_sum_of_rows(size_t dest, size_t src_a, size_t src_b) {
        if (dest >= H || src_a >= H || src_b >= H) {
            throw std::out_of_range("out of bounds reading matrix entry: "
                                    "Mat::set_row_to_sum_of_rows");
        }
        rows[dest] = add_elem_wise(rows[src_a], rows[src_b]);
    }

    /**
     * set a row to the sum of two other rows in the matrix, all zero-indexed,
     * with scalars paramters: (dest, src_a, scale_a, src_b, scale_b)
     * where
     * R_dest <== R_src_a * scale_a + R_src_b * scale_b
     */
    void set_row_to_sum_of_rows(size_t dest, size_t src_a, T scale_a,
                                size_t src_b, T scale_b) {
        if (dest >= H || src_a >= H || src_b >= H) {
            throw std::out_of_range("out of bounds reading matrix entry: "
                                    "Mat::set_row_to_sum_of_rows");
        }
        // create temp scaled vectors from the source rows
        auto temp_a = rows[src_a];
        scale(temp_a, scale_a);
        auto temp_b = rows[src_b];
        scale(temp_b, scale_b);
        // sum elem-wise and put into dest
        rows[dest] = add_elem_wise(temp_a, temp_b);
    }

    // get the row count of the matrix
    size_t row_count() { return H; }

    // get the column count of the matrix
    size_t col_count() { return W; }

    // get the string representation of the matrix
    std::string to_string() const {
        std::stringstream sstr;

        for (const auto& row : rows) {
            sstr << '{';

            for (size_t i = 0; i < row.size(); i++) {
                const auto& elem = row[i];

                if constexpr (std::is_floating_point_v<T>) {
                    // for floating point, account for print_precision
                    sstr << std::setw(4 + print_precision) << std::fixed
                         << std::setprecision(print_precision) << elem;
                } else {
                    sstr << std::setw(3) << elem;
                }

                if (i + 1 < row.size()) {
                    sstr << ", ";
                }
            }

            sstr << "}\n";
        }

        return sstr.str();
    }

    /**
     * move a row of type vector<T> into the matrix
     * the length of the row must match the dimensions of the matrix
     */
    void move_row_into(size_t row_idx, const std::vector<T>&& row) {
        if (row.size() != W) {
            throw std::out_of_range("invalid size when trying to move row into "
                                    "matrix: Mat::move_row_into");
        }
        if (row_idx >= H) {
            throw std::out_of_range("invalid row_idx to move into specified for"
                                    "matrix: Mat::move_row_into");
        }
        rows.at(row_idx) = row;
    }

    /**
     * copy a row of type vector<T> into the matrix
     * the length of the row must match the dimensions of the matrix
     *
     * this is slower than Mat::move_row_into, but is preferred if the row you
     * want to add into the matrix is an expiring value
     */
    void copy_row_into(size_t row_idx, const std::vector<T>& row) {
        if (row.size() != W) {
            throw std::out_of_range("invalid size when trying to copy row into "
                                    "matrix: Mat::move_row_into");
        }
        if (row_idx >= H) {
            throw std::out_of_range("invalid row_idx to copy into specified for"
                                    "matrix: Mat::move_row_into");
        }
        rows.at(row_idx) = row;
    }

    /**
     * calculate and return the rref of this matrix
     *
     * adapted from:
     * https://stackoverflow.com/questions/31756413/solving-a-simple-matrix-in-row-reduced-form-in-c
     */
    void rref() {
        size_t lead = 0;

        while (lead < H) {
            T d;
            T m;

            for (int r = 0; r < H; r++) { // for each row ...
                /* calculate divisor and multiplier */
                d = rows[lead][lead];
                m = rows[r][lead] / rows[lead][lead];

                for (int c = 0; c < W; c++) { // for each column ...
                    if (r == lead) {
                        rows[r][c] /= d; // make pivot = 1
                    } else {
                        rows[r][c] -= rows[lead][c] * m; // make other = 0
                    }
                }
            }
            lead++;
        }
    }
    /**
     * creates a new rref of this matrix by value
     */
    [[nodiscard("use .rref() if you want to take the rref of a Mat inplace")]]
    Mat make_rref() const {
        Mat copy;
        copy.rows = this->rows; // copy rows
        copy.rref();
        return copy;
    }

    /**
     * set print precision for floating point matrices
     */
    void set_print_precision(size_t precision) {
        // restrict max precision
        constexpr int MAX_PRECISION = 7;
        if (precision > MAX_PRECISION) {
            throw std::logic_error("requested print precision too high: "
                                   "Mat::set_print_precision\n");
        }
        this->print_precision = (int)precision;
    }
};

// overload allowing easy cout interop with the Mat class
template <size_t H, size_t W, typename T>
std::ostream& operator<<(std::ostream& os, const Mat<H, W, T>& mat) {
    os << mat.to_string();
    return os;
}

/**
 * matrix multiplication
 * number of rows of first mat must equal number of columns of the second mat
 *
 * adapted from: https://www.geeksforgeeks.org/c/c-matrix-multiplication/
 */
template <size_t A, size_t B, size_t C, size_t D, typename T>
Mat<A, D, T> multiply(const Mat<A, B, T>& m1, const Mat<C, D, T>& m2) {
    Mat<A, D, T> result;
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < D; j++) {
            result[i][j] = 0;

            for (int k = 0; k < D; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}
} // namespace m52l
#endif // !MATH0520LIB_MAT_HPP
