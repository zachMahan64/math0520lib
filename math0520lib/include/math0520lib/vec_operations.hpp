// math0520lib
// https://github.com/zachMahan64/math0520lib
// 2025
// Created by Zach Mahan

#ifndef MATH0520LIB_VEC_HPP
#define MATH0520LIB_VEC_HPP

#include <concepts>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace m52l {

template <class T>
concept IsString = requires(T s) {
    { s.c_str() };
};

template <class T>
concept NumericVec = !IsString<T> && requires(T v, size_t i) {
    { v.size() } -> std::convertible_to<size_t>;
    { v.at(i) } -> std::convertible_to<int>; // ensure numeric
};

/**
 * std::vector overload for dot products, prefer this for operations on very
 * large vectors
 */
template <class T>
    requires std::is_integral_v<T> || std::is_floating_point_v<T>
[[nodiscard]] T dot(const std::vector<T>& v, const std::vector<T>& u) {
    if (v.size() != u.size()) {
        throw std::logic_error(
            "lengths of vectors do not match when taking dot product");
    }
    T accum = 0;
    for (size_t i = 0; i < v.size(); i++) {
        accum += v[i] * u[i];
    }
    return accum;
}

/**
 * std::array overlaod for dot products, prefer this for most operations
 */
template <class T, size_t N>
    requires std::is_integral_v<T> || std::is_floating_point_v<T>
[[nodiscard]] T dot(const std::array<T, N>& v, const std::array<T, N>& u) {
    T accum = 0;
    for (size_t i = 0; i < v.size(); i++) {
        accum += v[i] * u[i];
    }
    return accum;
}

/**
 * perform elem-wise addition, can take any NumericVec, but always returns an
 * std::vector
 *
 * arguments must contain the same underlying type
 */
template <NumericVec V, NumericVec U>
    requires std::is_same_v<typename V::value_type, typename U::value_type>
[[nodiscard]] std::vector<typename V::value_type> add_elem_wise(const V& v,
                                                                const U& u) {
    if (v.size() != u.size()) {
        throw std::logic_error(
            "lengths of vectors do not match when doing elem-wise addition");
    }
    std::vector<typename V::value_type> res;
    for (size_t i = 0; i < v.size(); i++) {
        res.emplace_back(v[i] + u[i]);
    }
    return res;
}

template <NumericVec A, NumericVec B>
[[nodiscard]] auto cross(const A& a, const B& b) {
    if (a.size() != 3 || b.size() != 3) {
        throw std::logic_error("attempted to cross vectors that are not 3D");
    }
    using T =
        std::common_type_t<typename A::value_type, typename B::value_type>;
    // cross logic, always return a std::array for efficiency/simplicity
    return std::array<T, 3>{(a[1] * b[2]) - (a[2] * b[1]),
                            (a[2] * b[0]) - (a[0] * b[2]),
                            (a[0] * b[1]) - (a[1] * b[0])};
}

template <NumericVec T>
std::string vec_to_string(const T& vec) {
    std::stringstream sstr;
    sstr << '{';
    for (size_t i = 0; i < vec.size(); i++) {
        sstr << vec.at(i);
        if (i < vec.size() - 1) {
            sstr << ", ";
        }
    }
    sstr << '}';
    return sstr.str();
}
template <NumericVec T>
void scale(T& vec, typename T::value_type scalar) {
    for (auto& entry : vec) {
        entry *= scalar;
    }
}
} // namespace m52l

// overload allowing easy cout interop with our NumericVec concept
template <m52l::NumericVec T>
std::ostream& operator<<(std::ostream& os, const T& vec) {
    os << m52l::vec_to_string(vec);
    return os;
}

#endif // !MATH0520LIB_VEC_HPP
