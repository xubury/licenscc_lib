#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>

class Validator {
   public:
    static bool validate(const std::string &path);
    static std::string getIdentifier();
};

#endif  // !VALIDATOR_HPP
