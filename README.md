# LATTICE

An exact-arithmetic lattice computation engine 

The project is being developed incrementally. The first milestone establishes the integer and rational arithmetic foundations required for lattice algorithms.

## Current scope

- Arbitrary-precision integers through `boost::multiprecision::cpp_int`
- Normalized exact rational numbers
- Integer vectors
- Integer matrices
- Exact dot products and matrix multiplication
- Exact determinant calculation using fraction-free Bareiss elimination
- Initial unit tests

## Requirements

- CMake 3.20+
- C++20 compiler (GCC 11+, Clang 14+, or recent MSVC)
- Boost headers (Multiprecision is header-only)

On Debian/Ubuntu:

```bash
sudo apt install build-essential cmake libboost-dev
```

## Build and test

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the test executable directly:

```bash
./build/lattice_tests
```

## Repository structure

```text
include/lattice/   Public headers
src/               Implementations
tests/             Unit tests
docs/              Mathematical notes
```

## Mathematical conventions

- Integer arithmetic is exact and uses arbitrary precision.
- Rational numbers are always stored in reduced form.
- The determinant of the empty matrix is defined as 1.
- Matrix dimensions are checked at runtime; invalid operations throw `std::invalid_argument`.
- A square integer matrix is unimodular exactly when its determinant is +1 or -1.

## Development roadmap

1. Exact arithmetic and integer matrix foundation
2. Rational vectors and Gram-Schmidt orthogonalization
3. Unimodular basis transformations
4. LLL reduction
5. Babai nearest-plane algorithm
6. Shortest-vector experiments and benchmarks

## License

MIT. See `LICENSE`.
