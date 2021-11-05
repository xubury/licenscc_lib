#include <iostream>
#include <Validator.hpp>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cout << "Specify a path" << std::endl;
        return -1;
    }
    Validator::init();
    Validator::validate(argv[1]);
    return 0;
}
