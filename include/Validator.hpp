#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>

class Validator {
   public:
    static void init();
    static bool validate(const std::string &path);
};

#endif  // !VALIDATOR_HPP
