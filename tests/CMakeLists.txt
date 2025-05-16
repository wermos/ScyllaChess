cmake_minimum_required(VERSION 3.15)

add_subdirectory(../libs/Catch2)

file(GLOB_RECURSE TESTS_SOURCE
	CONFIGURE_DEPENDS
	*.cpp
)

add_executable(tests ${TESTS_SOURCE})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# catch_discover_tests(tests)
