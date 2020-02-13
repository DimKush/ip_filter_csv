cmake_minimum_required(VERSION 3.12)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(ENV{TRAVIS_BUILD_NUMBER} 1) #plug

project(ip_filter_csv VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost REQUIRED)

configure_file(version.vers ${PROJECT_SOURCE_DIR}/version.h)

add_executable(ip_filter_csv.out ${PROJECT_SOURCE_DIR}/src/main.cpp)


set_target_properties(ip_filter_csv.out PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS ip_filter_csv.out RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dimkysh@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
