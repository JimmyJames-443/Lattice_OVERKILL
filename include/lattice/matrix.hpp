#pragma once

#include "lattice/integer.hpp"
#include "lattice/vector.hpp"

#include <initializer_list>
#include <vector>

namespace lattice {

class Matrix {
public:
    Matrix() = default;
    Matrix(std::initializer_list<std::initializer_list<Integer>> rows);
    explicit Matrix(std::vector<std::vector<Integer>> rows);

    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;
    const Integer& operator()(std::size_t row, std::size_t col) const;
    Integer& operator()(std::size_t row, std::size_t col);

    Vector multiply(const Vector& vector) const;
    Matrix multiply(const Matrix& rhs) const;
    Integer determinant() const;
    bool is_unimodular() const;

private:
    std::vector<std::vector<Integer>> data_;
    std::size_t cols_ = 0;
};

}
