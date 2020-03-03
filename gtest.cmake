set(GTEST_LIB_DIR ./gtest/googletest CACHE STRING "Google Test source root")

message("{GTEST_LIB_DIR} = " ${GTEST_LIB_DIR})

message("{PROJECT_SOURCE_DIR} = " ${PROJECT_SOURCE_DIR})

include_directories(SYSTEM
    ${PROJECT_SOURCE_DIR}/${GTEST_LIB_DIR}
    ${PROJECT_SOURCE_DIR}/${GTEST_LIB_DIR}/include
    )

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GTEST_LIB_DIR}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GTEST_LIB_DIR}/src/gtest_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(gtest ${GOOGLETEST_SOURCES})