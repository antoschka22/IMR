#include <iostream>
#ifdef PATHS_SYSTEM
#include <imr_core/core.hpp>
#else
#include <core.hpp>
#endif

int main() {
    std::cout << imr_core::get_hello() << "\n";
    std::cout << "I am a program in a project using IMRCore!" << "\n";

    return 0;
}
