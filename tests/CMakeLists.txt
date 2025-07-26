cmake_minimum_required(VERSION 3.31)

add_subdirectory(../libs/Catch2 ${CMAKE_BINARY_DIR}/Catch2-build SYSTEM)

file(GLOB_RECURSE TESTS_SOURCE CONFIGURE_DEPENDS *.cpp)

add_executable(tests ${TESTS_SOURCE})

target_link_libraries(tests PRIVATE scylla_engine Catch2::Catch2WithMain)

# Add compiler flags to match your main targets
target_compile_options(
    tests
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>)

# Register the test executable with CTest
add_test(NAME scylla_tests COMMAND tests)

# Optional: Set test properties
set_tests_properties(scylla_tests PROPERTIES TIMEOUT 60 WORKING_DIRECTORY
                                             ${CMAKE_CURRENT_BINARY_DIR})
