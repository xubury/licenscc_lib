cmake_minimum_required(VERSION 3.1.0)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/release)
endif()

set(LCC_PROJECT_NAME DIAS_PROJECT)
project(licensecc_demo)

find_package(OpenSSL REQUIRED)
add_subdirectory(libs/licensecc)

add_library(validator 
    src/Validator.cpp)

set_property(TARGET validator PROPERTY CXX_STANDARD 17)

target_include_directories(validator PUBLIC include)
target_link_libraries(validator PRIVATE licensecc::licensecc_static)


add_executable(licensecc_demo src/main.cpp)

target_link_libraries(licensecc_demo validator)


