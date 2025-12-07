### Math0520lib: my bonus project made for Brown's Math 0520
- This library is header only, so using it as simple as including the [header files](math0520lib/include/math0520lib) in another project.
- The library contains a matrix class, `Mat`, that supports various row operations including an RREF method. There is also a matrix multiplication free function as well as a member function to calculate a matrix's determinant. There are free functions for scaling, dotting, and crossing vectors, as well as element-wise addition in the [vec_operations header](math0520lib/include/math0520lib/vec_operations.hpp). The matrix class is fully generic and interops cleanly with all standard numeric types (int, float, double, etc) and also interops with std::vector. It can also be initialized intuitively with initializer lists. The free functions for manipulating vectors also work generically with std::vectors and std::arrays containing standard numeric types. The library also comes with std::cout overloads for easy console printing of matrices and vectors, which you can see in the demo.
- Here is the output of the [demo code](demo/demo.cpp):
```
Hello, math0520! This is my demo for a basic C++ linear algebra library.
Here's a big matrix of all zeroes, the default value of any matrix we construct:
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}

We can take the dot and cross product of vectors:
v: {1, 2, 3}
u: {4, 5, 6}
dot product: 32
cross product: {-3, 6, -3}

Now, let's take the rref of some matrix!
original:
{  8,   2,   5}
{  4,   7,   1}
{  3,   8,   9}

rref:
{  1,   0,   0}
{  0,   1,   0}
{  0,   0,   1}

Now, let's take the rref of a bigger matrix!
original:
{ -8.00,   2.00,   5.00,   1.00,  -4.00,   6.00}
{  4.00,   7.00,   1.00,   0.00,   2.00,   6.00}
{  3.00,   8.00,   9.00,  -1.00,   3.00,   0.00}
{  0.00,  -4.00,   6.00,   3.00,   9.00,   1.00}
{ -1.00,   8.00,   2.00,   4.00,   5.00,   2.00}

rref:
{  1.00,   0.00,  -0.00,  -0.00,  -0.00,  17.47}
{  0.00,   1.00,  -0.00,  -0.00,   0.00,  -4.85}
{  0.00,   0.00,   1.00,   0.00,   0.00,   8.75}
{  0.00,   0.00,   0.00,   1.00,   0.00,  34.36}
{  0.00,   0.00,   0.00,   0.00,   1.00, -19.33}

We can also change the precision when printing floating point matrices.
Here's that same matrix but more *precise*:
{  1.00000,   0.00000,  -0.00000,  -0.00000,  -0.00000,  17.46912}
{  0.00000,   1.00000,  -0.00000,  -0.00000,   0.00000,  -4.85159}
{  0.00000,   0.00000,   1.00000,   0.00000,   0.00000,   8.75199}
{  0.00000,   0.00000,   0.00000,   1.00000,   0.00000,  34.36155}
{  0.00000,   0.00000,   0.00000,   0.00000,   1.00000, -19.33367}

Let's go back to vectors for a sec. We can scale them!
vector v: {1, 2, 3}, scaled by 5:
{5, 10, 15}

Back to matrices. We can do fun operations too!
let C = 
{  1.00,   3.00,   5.00,   1.00,   2.00}
{  6.00,   1.00,   3.00,   2.00,   2.00}
{ -4.00,   6.00,   2.00,   1.00,   8.00}
{ -4.00,   6.00,   2.00,   1.00,   8.00}
{ -5.00,   7.00,   3.00,   4.00,   1.00}
C after operation R3 <== -R4
{  1.00,   3.00,   5.00,   1.00,   2.00}
{  6.00,   1.00,   3.00,   2.00,   2.00}
{  4.00,  -6.00,  -2.00,  -1.00,  -8.00}
{ -4.00,   6.00,   2.00,   1.00,   8.00}
{ -5.00,   7.00,   3.00,   4.00,   1.00}

Next demo!
let D = 
{  1,   1,   1,   1,   1}
{  2,   2,   2,   2,   2}
{  3,   3,   3,   3,   3}
{  2,   2,   2,   2,   2}
{  2,   2,   2,   2,   2}
D after operation R1 <== (R2 + R4):
{  4,   4,   4,   4,   4}
{  2,   2,   2,   2,   2}
{  3,   3,   3,   3,   3}
{  2,   2,   2,   2,   2}
{  2,   2,   2,   2,   2}

Another row operation demo!
let E = 
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}
E after operation R1 <== (5*R2 + 5*R3):
{ 10,  10,  10,  10,  10}
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}
{  1,   1,   1,   1,   1}

Now, let's multiply some matrices!
let F = 
{  2,   3,   4,   5,   6}
{  7,   8,   9,   8,   7}
{  6,   5,   4,   3,   2}
{  1,   2,   3,   4,   5}
{  6,   7,   8,   9,   8}
let I5 = 
{  1,   0,   0,   0,   0}
{  0,   1,   0,   0,   0}
{  0,   0,   1,   0,   0}
{  0,   0,   0,   1,   0}
{  0,   0,   0,   0,   1}
F * I5 = 
{  2,   3,   4,   5,   6}
{  7,   8,   9,   8,   7}
{  6,   5,   4,   3,   2}
{  1,   2,   3,   4,   5}
{  6,   7,   8,   9,   8}
Determinant of F: 0
So it's not invertable.
```
### Building the Demo
- Make sure CMake, Make, and a C++ compiler are installed on your system
```bash
git clone https://github.com/zachMahan64/math0520lib.git
cd math0520lib
mkdir build
cd build
cmake ..
cd ..
cmake --build build
./build/demo