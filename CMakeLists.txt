cmake_minimum_required(VERSION 3.12)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)

project(ip_filter VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost REQUIRED)

configure_file(version.vers ${PROJECT_SOURCE_DIR}/version.h)

add_executable(ip_filter.out ${PROJECT_SOURCE_DIR}/src/main.cpp)


set_target_properties(ip_filter.out PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"

)