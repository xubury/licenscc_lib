#include "Validator.hpp"
#include <map>
#include <iostream>
#include <licensecc/licensecc.h>

static std::map<LCC_EVENT_TYPE, std::string> s_stringByEventType;

void Validator::init() {
    s_stringByEventType[LICENSE_OK] = "OK ";
    s_stringByEventType[LICENSE_FILE_NOT_FOUND] = "license file not found ";
    s_stringByEventType[LICENSE_SERVER_NOT_FOUND] =
        "license server can't be contacted ";
    s_stringByEventType[ENVIRONMENT_VARIABLE_NOT_DEFINED] =
        "environment variable not defined ";
    s_stringByEventType[FILE_FORMAT_NOT_RECOGNIZED] =
        "license file has invalid format (not .ini file) ";
    s_stringByEventType[LICENSE_MALFORMED] =
        "some mandatory field are missing, or data can't be fully read. ";
    s_stringByEventType[PRODUCT_NOT_LICENSED] =
        "this product was not licensed ";
    s_stringByEventType[PRODUCT_EXPIRED] = "license expired ";
    s_stringByEventType[LICENSE_CORRUPTED] =
        "license signature didn't match with current license ";
    s_stringByEventType[IDENTIFIERS_MISMATCH] =
        "Calculated identifier and the one provided in license didn't match";
}

bool Validator::validate(const std::string &path) {
    std::cout << "Validating license file from: " << path << std::endl;
    LicenseInfo licenseInfo;
    size_t pc_id_sz = LCC_API_PC_IDENTIFIER_SIZE + 1;
    char pc_identifier[LCC_API_PC_IDENTIFIER_SIZE + 1];

    LicenseLocation licenseLoc;
    licenseLoc.license_data_type = LICENSE_PATH;
    std::fill(licenseLoc.licenseData,
              licenseLoc.licenseData + sizeof(licenseLoc.licenseData), 0);
    std::copy(path.begin(), path.end(), licenseLoc.licenseData);

    LCC_EVENT_TYPE result = acquire_license(nullptr, &licenseLoc, &licenseInfo);
    if (result == LICENSE_OK) {
        std::cout << "license OK" << std::endl;
        if (!licenseInfo.linked_to_pc) {
            std::cout << "No hardware signature in license file. This is a "
                         "'demo' license that works on every pc."
                      << std::endl
                      << "To generate a 'single pc' license call 'issue "
                         "license' with option -s "
                      << std::endl
                      << "and the hardware identifier obtained before."
                      << std::endl;
            return false;
        } else {
            return true;
        }
    } else {
        std::cout << "license ERROR :" << std::endl;
        std::cout << "    " << s_stringByEventType[result].c_str() << std::endl;
        if (identify_pc(STRATEGY_DEFAULT, pc_identifier, &pc_id_sz, nullptr)) {
            std::cout << "hardware id is :" << std::endl;
            std::cout << "    " << pc_identifier << std::endl;
        } else {
            std::cerr << "errors in identify_pc" << std::endl;
        }
        return false;
    }
}
