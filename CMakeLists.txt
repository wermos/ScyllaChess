cmake_minimum_required(VERSION 3.31)

project(ScyllaChess VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(CXX)

# Enable testing to get the built-in 'test' target
enable_testing()

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(scylla_engine ${LIB_SOURCES})
target_include_directories(scylla_engine PUBLIC include)

# Configure libassert options
set(LIBASSERT_USE_EXTERNAL_CPPTRACE
    OFF
    CACHE BOOL "Disable external cpptrace")
set(LIBASSERT_BUILD_TESTING
    OFF
    CACHE BOOL "Disable libassert tests")
set(CMAKE_SKIP_INSTALL_RULES
    OFF
    CACHE BOOL "Skip CMake Install Rules")

add_subdirectory(libs/libassert ${CMAKE_BINARY_DIR}/libassert-build SYSTEM)
target_link_libraries(scylla_engine PUBLIC libassert::assert)

# Main executable
add_executable(scylla src/main.cpp)
target_link_libraries(scylla PRIVATE scylla_engine)

# Compiler flags
target_compile_options(
    scylla_engine
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>)

target_compile_options(
    scylla
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>)

# Add tests subdirectory - include in 'all' target
add_subdirectory(tests)

# Custom target: Build only the core library
add_custom_target(
    library
    DEPENDS scylla_engine
    COMMENT "Building core library only")

# Custom target: Build library + main executable (engine)
add_custom_target(
    engine
    DEPENDS scylla_engine scylla
    COMMENT "Building library and main executable")

# Built-in targets: 'test' - runs tests (created by enable_testing()) 'all' -
# builds everything: library + executable + tests
