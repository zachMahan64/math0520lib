#include "math0520lib/mat.hpp"
#include <iostream>

int main(int argc, char** argv) {
    Mat<12, 11, float> mat;
    std::cout << "Hello, math0520! This is my demo for a basic C++ linear "
                 "algebra library."
              << '\n';

    std::cout << mat;

    Mat<2, 2, float> mat1({{2, 2}, {1, 1}});
    mat1.copy_row_to_from(1, 0);
    std::cout << mat1.at(1, 1) << '\n';

    std::cout << mat1;
    return 0;
}
