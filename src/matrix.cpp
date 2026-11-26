#include "lattice/matrix.hpp"

#include <stdexcept>
#include <utility>

namespace lattice {

Matrix::Matrix(std::initializer_list<std::initializer_list<Integer>> rows) {
    data_.reserve(rows.size());
    for (const auto& row : rows) {
        data_.emplace_back(row);
    }
    cols_ = data_.empty() ? 0 : data_.front().size();
    for (const auto& row : data_) {
        if (row.size() != cols_) {
            throw std::invalid_argument("Matrix rows must have equal lengths");
        }
    }
}

Matrix::Matrix(std::vector<std::vector<Integer>> rows) : data_(std::move(rows)) {
    cols_ = data_.empty() ? 0 : data_.front().size();
    for (const auto& row : data_) {
        if (row.size() != cols_) {
            throw std::invalid_argument("Matrix rows must have equal lengths");
        }
    }
}

std::size_t Matrix::rows() const noexcept { return data_.size(); }
std::size_t Matrix::cols() const noexcept { return cols_; }

const Integer& Matrix::operator()(std::size_t row, std::size_t col) const {
    return data_.at(row).at(col);
}

Integer& Matrix::operator()(std::size_t row, std::size_t col) {
    return data_.at(row).at(col);
}

Vector Matrix::multiply(const Vector& vector) const {
    if (cols_ != vector.size()) {
        throw std::invalid_argument("Matrix and vector dimensions do not match");
    }
    std::vector<Integer> result(rows(), 0);
    for (std::size_t i = 0; i < rows(); ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result[i] += data_[i][j] * vector[j];
        }
    }
    return Vector(std::move(result));
}

Matrix Matrix::multiply(const Matrix& rhs) const {
    if (cols_ != rhs.rows()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    std::vector<std::vector<Integer>> result(rows(), std::vector<Integer>(rhs.cols(), 0));
    for (std::size_t i = 0; i < rows(); ++i) {
        for (std::size_t k = 0; k < cols_; ++k) {
            for (std::size_t j = 0; j < rhs.cols(); ++j) {
                result[i][j] += data_[i][k] * rhs(k, j);
            }
        }
    }
    return Matrix(std::move(result));
}

Integer Matrix::determinant() const {
    if (rows() != cols_) {
        throw std::invalid_argument("Determinant requires a square matrix");
    }
    const std::size_t n = rows();
    if (n == 0) return 1;
    if (n == 1) return data_[0][0];

    auto work = data_;
    Integer previous_pivot = 1;
    int sign = 1;

    for (std::size_t k = 0; k + 1 < n; ++k) {
        if (work[k][k] == 0) {
            std::size_t pivot_row = k + 1;
            while (pivot_row < n && work[pivot_row][k] == 0) {
                ++pivot_row;
            }
            if (pivot_row == n) return 0;
            std::swap(work[k], work[pivot_row]);
            sign = -sign;
        }

        const Integer pivot = work[k][k];
        for (std::size_t i = k + 1; i < n; ++i) {
            for (std::size_t j = k + 1; j < n; ++j) {
                const Integer numerator = work[i][j] * pivot - work[i][k] * work[k][j];
                if (numerator % previous_pivot != 0) {
                    throw std::logic_error("Bareiss exact-division invariant failed");
                }
                work[i][j] = numerator / previous_pivot;
            }
            work[i][k] = 0;
        }
        previous_pivot = pivot;
    }

    return sign * work[n - 1][n - 1];
}

bool Matrix::is_unimodular() const {
    const Integer det = determinant();
    return det == 1 || det == -1;
}

}
