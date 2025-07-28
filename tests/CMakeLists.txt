cmake_minimum_required(VERSION 3.31)

add_subdirectory(../libs/Catch2 ${CMAKE_BINARY_DIR}/Catch2-build SYSTEM)

# # Get all test files individually
file(GLOB TESTS_SOURCE CONFIGURE_DEPENDS *.cpp)

add_executable(tests ${TESTS_SOURCE})
target_link_libraries(tests PRIVATE scylla_engine Catch2::Catch2WithMain)

target_compile_options(
    tests
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>)

include(Catch)
include(CTest)

catch_discover_tests(tests)
