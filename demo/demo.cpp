// math0520lib
// https://github.com/zachMahan64/math0520lib
// 2025
// Created by Zach Mahan

#include "demo.hpp"
#include "math0520lib/mat.hpp"
#include "math0520lib/vec_operations.hpp"
#include <iostream>

void run_demo() {
    using namespace m52l;
    using std::cout;
    cout << "Hello, math0520! This is my demo for a basic C++ linear "
            "algebra library."
         << '\n';

    // demo 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Here's a big matrix of all zeroes, the default value of any "
            "matrix we construct:"
         << '\n';
    Mat<12, 11, int> mat_big;
    std::cout << mat_big << '\n';

    // demo 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout << "We can take the dot and cross product of vectors:\n";
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
    cout << v << "\n\n";

    // demo 6 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Back to matrices. We can do fun operations too!\n";
    int row_scalar = 5;
    Mat<5, 5, double> C = {{1, 3, 5, 1, 2},
                           {6, 1, 3, 2, 2},
                           {-4, 6, 2, 1, 8},
                           {-4, 6, 2, 1, 8},
                           {-5, 7, 3, 4, 1}};
    cout << "let C = \n";
    cout << C;
    // rows are zero indexed. this method takes parameters (dest, src, scalar):
    C.row_into_from(2, 3, -1);
    cout << "C after operation R3 <== -R4\n";
    cout << C << '\n';

    // demo 7 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Next demo!" << "\n";
    // let's use 16-bit integers for funsies
    Mat<5, 5, int16_t> D = {{1, 1, 1, 1, 1},
                            {2, 2, 2, 2, 2},
                            {3, 3, 3, 3, 3},
                            {2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2}};
    cout << "let D = \n";
    cout << D;
    // rows are zero indexed. this method takes parameters (dest, src_a, src_b):
    D.set_row_to_sum_of_rows(0, 1, 3);
    cout << "D after operation R1 <== (R2 + R4):\n";
    cout << D << '\n';

    // demo 8 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Another row operation demo!" << "\n";
    Mat<5, 5, long> E = {{1, 1, 1, 1, 1},
                         {1, 1, 1, 1, 1},
                         {1, 1, 1, 1, 1},
                         {1, 1, 1, 1, 1},
                         {1, 1, 1, 1, 1}};
    cout << "let E = \n";

    cout << E;
    // rows are zero indexed.
    // this method takes parameters (dest, src_a, scale_a, src_b, scale_b):
    E.set_row_to_sum_of_rows(0, 1, 5, 2, 5);
    cout << "E after operation R1 <== (5*R2 + 5*R3):\n";
    cout << E << '\n';

    // demo 9 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Now, let's multiply some matrices!" << "\n";
    // let's use 16-bit integers for funsies
    Mat<5, 5, int> F = {{2, 3, 4, 5, 6},
                        {7, 8, 9, 8, 7},
                        {6, 5, 4, 3, 2},
                        {1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 8}};
    cout << "let F = \n";
    cout << F;
    Mat<5, 5, int> I5 = {{1, 0, 0, 0, 0},
                         {0, 1, 0, 0, 0},
                         {0, 0, 1, 0, 0},
                         {0, 0, 0, 1, 0},
                         {0, 0, 0, 0, 1}};
    cout << "let I5 = \n";
    cout << I5;
    cout << "F * I5 = \n";
    cout << multiply(F, I5);
    cout << "Determinant of F: " << F.det() << '\n';
    cout << "So it's not invertable." << '\n';
}
