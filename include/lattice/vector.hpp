#pragma once

#include "lattice/integer.hpp"

#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lattice {

class Vector {
public:
    Vector() = default;
    Vector(std::initializer_list<Integer> values) : values_(values) {}
    explicit Vector(std::vector<Integer> values) : values_(std::move(values)) {}

    std::size_t size() const noexcept { return values_.size(); }
    const Integer& operator[](std::size_t index) const { return values_.at(index); }
    Integer& operator[](std::size_t index) { return values_.at(index); }
    const std::vector<Integer>& values() const noexcept { return values_; }

    Integer dot(const Vector& rhs) const {
        if (size() != rhs.size()) {
            throw std::invalid_argument("Vector dimensions do not match");
        }
        Integer result = 0;
        for (std::size_t i = 0; i < size(); ++i) {
            result += values_[i] * rhs.values_[i];
        }
        return result;
    }

    Integer norm_squared() const { return dot(*this); }

    friend bool operator==(const Vector&, const Vector&) = default;

private:
    std::vector<Integer> values_;
};

}
