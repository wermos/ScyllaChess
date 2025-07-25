cmake_minimum_required(VERSION 3.31)

add_subdirectory(../libs/Catch2
                 ${CMAKE_BINARY_DIR}/Catch2-build
                 SYSTEM)

file(GLOB_RECURSE TESTS_SOURCE
    CONFIGURE_DEPENDS
    *.cpp
)

add_executable(tests ${TESTS_SOURCE})

target_link_libraries(tests PRIVATE scylla_engine Catch2::Catch2WithMain)
