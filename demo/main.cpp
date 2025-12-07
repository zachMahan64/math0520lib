#include "demo.hpp"
#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    try {
        run_demo();
    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] There were some issues when running your code:"
                  << '\n';
        std::cerr << e.what() << '\n';
    }
    return 0;
}
