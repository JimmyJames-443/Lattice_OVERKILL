#pragma once

#include "lattice/integer.hpp"

#include <iosfwd>

namespace lattice {

class Rational {
public:
    Rational();
    Rational(long long value);
    Rational(Integer numerator, Integer denominator = 1);

    const Integer& numerator() const noexcept;
    const Integer& denominator() const noexcept;

    Rational operator-() const;
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    friend Rational operator+(Rational lhs, const Rational& rhs) { return lhs += rhs; }
    friend Rational operator-(Rational lhs, const Rational& rhs) { return lhs -= rhs; }
    friend Rational operator*(Rational lhs, const Rational& rhs) { return lhs *= rhs; }
    friend Rational operator/(Rational lhs, const Rational& rhs) { return lhs /= rhs; }

    friend bool operator==(const Rational&, const Rational&) = default;
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Rational& value);

private:
    Integer numerator_;
    Integer denominator_;
    void normalize();
};

}
