#ifndef MATH0520LIB_MAT_HPP
#define MATH0520LIB_MAT_HPP
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

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
     * I did not come up with this algorithm; I adapted it from here:
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
#endif // !MATH0520LIB_MAT_HPP
