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

# -Werror
target_compile_options(scylla PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

target_include_directories(scylla PUBLIC include)
