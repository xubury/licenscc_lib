#include "Validator.hpp"
#include <map>
#include <iostream>
#include <licensecc/licensecc.h>
#include <filesystem>

const std::map<LCC_EVENT_TYPE, std::string> s_stringByEventType = {
    {LICENSE_OK, "OK "},
    {LICENSE_FILE_NOT_FOUND, "license file not found "},
    {LICENSE_SERVER_NOT_FOUND, "license server can't be contacted "},
    {ENVIRONMENT_VARIABLE_NOT_DEFINED, "environment variable not defined "},
    {FILE_FORMAT_NOT_RECOGNIZED,
     "license file has invalid format (not .ini file) "},
    {LICENSE_MALFORMED,
     "some mandatory field are missing, or data can't be fully read. "},
    {PRODUCT_NOT_LICENSED, "this product was not licensed "},
    {PRODUCT_EXPIRED, "license expired "},
    {LICENSE_CORRUPTED, "license signature didn't match with current license "},
    {IDENTIFIERS_MISMATCH,
     "Calculated identifier and the one provided in license didn't match"}};

const LCC_API_HW_IDENTIFICATION_STRATEGY strategy = STRATEGY_DISK;

bool Validator::validate(const std::string &path) {
    auto p = std::filesystem::path(path);
    if (p.is_relative()) {
        p = std::filesystem::current_path() / p;
    }
    std::cout << "Validating license file from: " << p << std::endl;
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
            return false;
        } else {
            return true;
        }
    } else {
        std::cout << "license ERROR :" << std::endl;
        std::cout << "    " << s_stringByEventType.at(result).c_str()
                  << std::endl;
        return false;
    }
}

std::string Validator::getIdString() {
    size_t pc_id_sz = LCC_API_PC_IDENTIFIER_SIZE + 1;
    char pc_identifier[LCC_API_PC_IDENTIFIER_SIZE + 1];
    if (identify_pc(strategy, pc_identifier, &pc_id_sz, nullptr)) {
        return pc_identifier;
    } else {
        std::cerr << "errors in identify_pc" << std::endl;
        return "";
    }
}
