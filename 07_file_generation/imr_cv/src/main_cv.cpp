#include <iostream>
#include <imr_core/version.hpp>

int main() {
    std::cout << "Running imr_cv with IMRCore version: " << imr::get_version_string() << "\n";
    return 0;
}
