cmake_minimum_required(VERSION 3.15)

project(ScyllaChess VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(CXX)

file(GLOB_RECURSE SOURCES
	CONFIGURE_DEPENDS
	src/*.cpp
)

add_executable(scylla ${SOURCES})

if (BUILD_TESTING)
	add_subdirectory(libs/Catch2)

	file(GLOB_RECURSE TESTS_SOURCE
		CONFIGURE_DEPENDS
		tests/*.cpp
	)

	add_executable(engine_tests ${TESTS_SOURCE})

	target_include_directories(engine_tests PUBLIC include)

	target_link_libraries(engine_tests PRIVATE Catch2::Catch2WithMain)
endif()

target_include_directories(scylla PUBLIC include)
