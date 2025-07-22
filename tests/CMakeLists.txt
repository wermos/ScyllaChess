cmake_minimum_required(VERSION 3.31)

add_subdirectory(../libs/Catch2
                 ${CMAKE_BINARY_DIR}/Catch2-build # Binary directory
                 SYSTEM)

file(GLOB_RECURSE TESTS_SOURCE
    CONFIGURE_DEPENDS
    *.cpp
)

add_executable(tests ${TESTS_SOURCE})
target_include_directories(tests PUBLIC ../include)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
