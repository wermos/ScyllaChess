![Build Status](https://github.com/wermos/ScyllaChess/actions/workflows/build.yml/badge.svg) ![Tests Status](https://github.com/wermos/ScyllaChess/actions/workflows/runtests.yaml/badge.svg) ![License](https://img.shields.io/github/license/wermos/ScyllaChess) 

## Prerequisites

* CMake 3.31+
* C++23 compatible compiler:
  * GCC 13+ (Linux)
  * Clang 16+ (macOS)
  * MSVC 2022+ (Windows)

## Getting Started

Clone the repository:

```bash
git clone --recursive https://github.com/wermos/ScyllaChess.git
cd ScyllaChess
```

Note: The `--recursive` flag is essential as the project uses git submodules (`libassert` and `Catch2`).

## Building the Project

### Quick Start - Build Everything

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target all
```

### Targeted Builds

The project provides several build targets for different needs:

#### Build Core Library Only

```bash
cmake --build build --target library
```

Builds only the ```scylla_engine``` library.

#### Build Engine (Library + Executable)

```bash
cmake --build build --target engine
```

Builds the library and main executable. Run with:
```bash
./build/scylla
```

#### Build Tests

```bash
cmake --build build --target tests
```

#### Build Everything

```bash
cmake --build build --target all
```

### Running Tests

#### Build and Run Tests

```bash
# Configure with testing enabled
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

# Build all targets including tests
cmake --build build --target all

# Run tests using CTest
ctest --test-dir build --output-on-failure
```

Or run tests using CMake's `test` target
```bash
cmake --build build --target test
```

##### Running Specific Tests

```bash
# Run tests matching a pattern
ctest --test-dir build -R "test_name_pattern" --output-on-failure

# Run the test executable directly
./build/tests/tests
```

## Development Setup

### Pre-commit Hooks

This project uses pre-commit hooks to ensure code quality and consistent formatting.

#### First-time Setup

Install pre-commit:

```bash
pip install pre-commit
```

Install the hooks:

```bash
pre-commit install --hook-type pre-commit
pre-commit install --hook-type pre-push
```

Install required tools for C++ formatting
```bash
sudo apt-get install clang-format # Ubuntu/Debian
brew install clang-format # macOS
```

and CMake formatting
```bash
pip install cmake-format
```

### Using Pre-commit

#### Automatic formatting (runs on commit and push):

Code is automatically formatted when you `git commit`. Additional checks run when you `git push`.

#### Manual formatting

```bash
#Format all files
pre-commit run --all-files

# Format only staged files
pre-commit run

# Run specific hooks
pre-commit run clang-format --all-files
```

You can skip hooks by using:

```bash
git commit --no-verify # Skip pre-commit hooks
git push --no-verify # Skip pre-push hooks
```

But this is not recommended.

### Coding Style

Formatting is done using `clang-format`. We follow Google's coding style with one modification: we use 4-space indents instead of 4-space indents.

CMake is formatted using `cmake-format`.

#### Naming

* Class names use `PascalCase`.
* Functions and variable names use `snake_case`.
* Member variables use `m_snake_case`.

## Contributing

* Fork and clone the repository with submodules.

* Set up pre-commit hooks (see Development Setup)

* Create a feature branch: `git checkout -b feature/amazing-feature`

* Make your changes and ensure tests pass

* Push and create a pull request

### Running CI Locally

```bash
# Check formatting
pre-commit run --all-files

# Build like CI
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target engine

# Test like CI
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build --target all
cmake --build build --target test
```
