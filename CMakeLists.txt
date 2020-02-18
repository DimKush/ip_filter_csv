cmake_minimum_required(VERSION 3.12)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(ENV{TRAVIS_BUILD_NUMBER} 1) #plug

project(ip_filter_csv VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost REQUIRED)

configure_file(version.vers ${PROJECT_SOURCE_DIR}/version.h)

add_executable(ip_filter_csv.out ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(ip_filter_csv_unit_test_lib ${PROJECT_SOURCE_DIR}/lib/lib.cpp)

add_executable(ip_filter_csv_unit_test.out ${PROJECT_SOURCE_DIR}/src/unit.cpp)

set_target_properties( ip_filter_csv.out ip_filter_csv_unit_test.out ip_filter_csv_unit_test_lib PROPERTIES
                       CXX_STANDARD 17
                       CXX_STANDARD_REQUIRED ON
                       COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties( ip_filter_csv_unit_test.out PROPERTIES
                       COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
                       INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(  ip_filter_csv.out
                        ip_filter_csv_unit_test_lib
)

target_link_libraries( ip_filter_csv_unit_test.out
                       ${Boost_LIBRARIES}
                       ip_filter_csv_unit_test_lib                 
)




install(TARGETS ip_filter_csv.out RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dimkysh@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(unit_test ip_filter_csv_unit_test.out)