#include "demo.hpp"
#include "math0520lib/mat.hpp"
#include "math0520lib/vec_operations.hpp"
#include <iostream>

void run_demo() {
    using std::cout;
    cout << "Hello, math0520! This is my demo for a basic C++ linear "
            "algebra library."
         << '\n';

    // demo 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Here's a big matrix of all zeroes, which is easy to initialze:" << '\n';
    Mat<12, 11, float> mat_big;
    std::cout << mat_big << '\n';

    // demo 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::vector<int> v{1, 2, 3};
    std::vector<int> u{4, 5, 6};
    cout << "v: " << v;
    cout << "u: " << u;
    cout << "dot product: " << dot(v, u) << '\n';
    cout << "cross product: " << cross(v, u) << "\n\n";

    // demo 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Now, let's take the rref of some matrix!" << "\n";
    Mat<3, 3, int> mat({{8, 2, 5}, {4, 7, 1}, {3, 8, 9}});
    std::cout << "original:\n" << mat << '\n';
    std::cout << "rref:\n" << mat.make_rref() << '\n';

    // demo 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Now, let's take the rref of a bigger matrix!" << "\n";
    // this time, we'll use a matrix of doubles
    Mat<5, 6, double> mat1({{-8, 2, 5, 1, -4, 6},
                            {4, 7, 1, 0, 2, 6},
                            {3, 8, 9, -1, 3, 0},
                            {0, -4, 6, 3, 9, 1},
                            {-1, 8, 2, 4, 5, 2}});
    std::cout << "original:\n" << mat1 << '\n';
    mat1.rref(); // this modifies the matrix and turns it into its rref in
                 // place
    std::cout << "rref:\n" << mat1 << '\n';

    // demo 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout << "we can also change the precision of floating point matrices.\n";
    std::cout << "here's that same matrix but more *precise*:\n";
    mat1.set_print_precision(5);
    std::cout << mat1;
}
