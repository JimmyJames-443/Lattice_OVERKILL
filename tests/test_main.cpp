#include "lattice/matrix.hpp"
#include "lattice/rational.hpp"
#include "lattice/vector.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {

int failures = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
    } else {
        std::cerr << "[FAIL] " << name << '\n';
        ++failures;
    }
}

template <typename Function>
void check_throws(Function function, const std::string& name) {
    try {
        function();
        check(false, name);
    } catch (const std::exception&) {
        check(true, name);
    }
}

}

int main() {
    using lattice::Integer;
    using lattice::Matrix;
    using lattice::Rational;
    using lattice::Vector;

    const Vector a{1, 2, 3};
    const Vector b{4, 5, 6};
    check(a.dot(b) == 32, "integer vector dot product");
    check(a.norm_squared() == 14, "squared Euclidean norm");
    check_throws([&] { (void)a.dot(Vector{1, 2}); }, "vector dimension mismatch");

    const Rational r1(Integer(2), Integer(4));
    const Rational r2(Integer(1), Integer(6));
    check(r1 == Rational(Integer(1), Integer(2)), "rational normalization");
    check(r1 + r2 == Rational(Integer(2), Integer(3)), "rational addition");
    check(r1 - r2 == Rational(Integer(1), Integer(3)), "rational subtraction");
    check(r1 * r2 == Rational(Integer(1), Integer(12)), "rational multiplication");
    check(r1 / r2 == Rational(3), "rational division");
    check_throws([] { (void)Rational(Integer(1), Integer(0)); }, "zero denominator rejected");
    check_throws([] { (void)(Rational(1) / Rational(0)); }, "division by zero rejected");

    const Matrix m{{1, 2}, {3, 4}};
    check(m.determinant() == -2, "2x2 determinant");

    const Matrix swap_rows{{0, 1}, {1, 0}};
    check(swap_rows.determinant() == -1, "determinant with row pivoting");
    check(swap_rows.is_unimodular(), "unimodular matrix detection");

    const Matrix singular{{1, 2}, {2, 4}};
    check(singular.determinant() == 0, "singular determinant");

    const Matrix large{{Integer("100000000000000000000"), 1}, {1, 3}};
    check(large.determinant() == Integer("299999999999999999999"),
          "arbitrary-precision determinant");

    const Matrix left{{1, 2, 3}, {4, 5, 6}};
    const Matrix right{{7, 8}, {9, 10}, {11, 12}};
    const Matrix product = left.multiply(right);
    check(product(0, 0) == 58 && product(1, 1) == 154, "matrix multiplication");

    const Vector transformed = m.multiply(Vector{2, 3});
    check(transformed == Vector{8, 18}, "matrix-vector multiplication");

    check_throws([] { (void)Matrix{{1, 2}, {3}}; }, "ragged matrix rejected");
    check_throws([] { (void)Matrix{{1, 2, 3}, {4, 5, 6}}.determinant(); }, "square determinant validation");

    std::cout << "\n";
    if (failures != 0) {
        std::cerr << failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}
