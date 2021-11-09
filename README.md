# licensecc_demo

## How to use
### Requirement
Boost

OpenSSL

### Issue a license
lccgen license issue -p `path/to/private-key` -s `hardware-id` -o `path/to/license`

### validate a license
licensecc_demo `path/to/license`

### use validator as lib
Link validator, include `Validator.hpp`

```cpp
  // validate license
  Validator::validate("path/to/license")
  // get hardware id
  std::cout << Validator::getIdentifier() << std::endl;
```
