#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>

class Validator {
   public:
    static bool Validate(const std::string &path);
    static std::string GetIdentifier();
};

#endif  // !VALIDATOR_HPP
