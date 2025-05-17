![Build Status](https://github.com/wermos/ScyllaChess/actions/workflows/build.yml/badge.svg) ![Tests Status](https://github.com/wermos/ScyllaChess/actions/workflows/runtests.yaml/badge.svg) ![License](https://img.shields.io/github/license/wermos/ScyllaChess) 

# ScyllaChess

## Building the Repo

To build the repo, run

```bash
cmake -S. -Bbuild
```

and then

```bash
cmake --build build
```

The executable will be inside the `build` directory and can be run via

```bash
./build/scylla
```

## Building the Repo With Tests

First, ensure that you have checked out the repo with its submodules. This can be done via
```bash
git checkout --recursive https://github.com/wermos/ScyllaChess.git
```

Then, run
```bash
cmake -S. -Bbuild -DBUILD_TESTING=ON
```

and then

```bash
cmake --build build --parallel
```

The tests can be run via

```bash
./build/tests/tests
```
