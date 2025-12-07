cmake --build build
{
echo "### math0520lib, bonus project made for Brown's Math 0520 Linear Algebra Course";
echo "- The library is header-only, see the [demo](demo/demo.cpp) for usage.";
echo "- The library contains a matrix class, \`Mat\`, that supports various row operations including an RREF method. There are also free functions
for scaling, dotting, and crossing vectors, as well as element-wise addition in [include/math0520lib](math0520lib/include/math0520lib). The matrix class is fully generic and interops cleanly with all standard numeric types (int, float, double, etc) and also interops with std::vector. It can also be initialized intuitively with initializer lists. The free functions for manipulating vectors also work generically with std::vectors and std::arrays containing standard numeric types.";
echo "- Using this library is as simple as including the [header files](math0520lib/include/math0520lib) in another project.";
echo "- Here is the output of the demo code:";
echo "\`\`\`";
./build/demo
echo "\`\`\`";
} > README.md
