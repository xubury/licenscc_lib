#include <iostream>
#include <Validator.hpp>

int main(int argc, char* argv[]) {
    std::cout << "hardware id: " << Validator::GetIdentifier() << std::endl;
    if (argc <= 1) {
        std::cout << "Specify a path" << std::endl;
        return -1;
    }
    Validator::Validate(argv[1]);
    return 0;
}
