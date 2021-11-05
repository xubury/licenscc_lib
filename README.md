# licensecc_demo

## How to use
### Requirement
Boost

OpenSSL

### Issue a license
./bin/lccgen license issue -p <path-to-private-key> -s <identifier> -o <path/to/license> 

### validate a license
./bin/licensecc_demo <path/to/license>


### use validator as lib
Link validator, include <Validator.hpp>

```cpp
  // first init validator
  Validator::init();
  ....
  Validator::validate("path/to/license")
```  
