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
    cout << "Here's a big matrix of all zeroes, which is easy to initialze:"
         << '\n';
    Mat<12, 11, float> mat_big;
    std::cout << mat_big << '\n';

    // demo 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::vector<int> v{1, 2, 3};
    std::vector<int> u{4, 5, 6};
    cout << "v: " << v << '\n';
    cout << "u: " << u << '\n';
    cout << "dot product: " << dot(v, u) << '\n';
    cout << "cross product: " << cross(v, u) << "\n\n";

    // demo 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Now, let's take the rref of some matrix!" << "\n";
    Mat<3, 3, int> A({{8, 2, 5}, {4, 7, 1}, {3, 8, 9}});
    cout << "original:\n" << A << '\n';
    cout << "rref:\n" << A.make_rref() << '\n';

    // demo 4 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Now, let's take the rref of a bigger matrix!" << "\n";
    // this time, we'll use a matrix of doubles
    Mat<5, 6, double> B({{-8, 2, 5, 1, -4, 6},
                         {4, 7, 1, 0, 2, 6},
                         {3, 8, 9, -1, 3, 0},
                         {0, -4, 6, 3, 9, 1},
                         {-1, 8, 2, 4, 5, 2}});
    cout << "original:\n" << B << '\n';
    B.rref(); // this modifies the matrix and turns it into its rref in
              // place
    cout << "rref:\n" << B << '\n';

    // demo 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "We can also change the precision when printing floating point "
            "matrices.\n";
    cout << "Here's that same matrix but more *precise*:\n";
    B.set_print_precision(5);
    cout << B << '\n';

    // demo 5 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Let's go back to vectors for a sec. We can scale them!\n";
    int scalar = 5;
    cout << "vector v: " << v << ", scaled by " << scalar << ":\n";
    scale(v, scalar); // modified in place
    cout << v << '\n';

    // demo 6 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Back to matrices. We can do fun operations too!\n";
    int row_scalar = 5;
    Mat<5, 5, double> C = {{1, 3, 5, 1, 2},
                           {6, 1, 3, 2, 2},
                           {-4, 6, 2, 1, 8},
                           {-4, 6, 2, 1, 8},
                           {-5, 7, 3, 4, 1}};
}
