# Algorithm roadmap

## Milestone 1: exact arithmetic kernel

- [x] Arbitrary-precision integer type
- [x] Canonical rational arithmetic
- [x] Integer vectors and dot products
- [x] Integer matrices and multiplication
- [x] Fraction-free determinant
- [x] Unimodularity predicate
- [x] Initial unit tests

## Milestone 2: rational linear algebra

- [ ] Rational vectors
- [ ] Exact Gram-Schmidt orthogonalization
- [ ] Linear independence detection
- [ ] Orthogonal coefficient matrix

## Milestone 3: lattice transformations

- [ ] Integer row/column operations
- [ ] Track transformation matrix U
- [ ] Verify det(U) = ±1
- [ ] Verify B_reduced = U * B_original

## Milestone 4: LLL

- [ ] Size reduction
- [ ] Lovász condition
- [ ] Basis swaps
- [ ] Exact-arithmetic implementation
- [ ] Termination and correctness tests
