#include "lattice/rational.hpp"

#include <ostream>
#include <stdexcept>

namespace lattice {
namespace {

Integer abs_integer(Integer value) {
    return value < 0 ? -value : value;
}

Integer gcd(Integer a, Integer b) {
    a = abs_integer(a);
    b = abs_integer(b);
    while (b != 0) {
        Integer remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

}

Rational::Rational() : numerator_(0), denominator_(1) {}

Rational::Rational(long long value) : numerator_(value), denominator_(1) {}

Rational::Rational(Integer numerator, Integer denominator)
    : numerator_(std::move(numerator)), denominator_(std::move(denominator)) {
    normalize();
}

const Integer& Rational::numerator() const noexcept { return numerator_; }
const Integer& Rational::denominator() const noexcept { return denominator_; }

void Rational::normalize() {
    if (denominator_ == 0) {
        throw std::invalid_argument("Rational denominator cannot be zero");
    }
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    const Integer divisor = gcd(numerator_, denominator_);
    numerator_ /= divisor;
    denominator_ /= divisor;
}

Rational Rational::operator-() const {
    return Rational(-numerator_, denominator_);
}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator_ = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
    denominator_ *= rhs.denominator_;
    normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    return *this += -rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator_ *= rhs.numerator_;
    denominator_ *= rhs.denominator_;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.numerator_ == 0) {
        throw std::invalid_argument("Division by zero rational");
    }
    numerator_ *= rhs.denominator_;
    denominator_ *= rhs.numerator_;
    normalize();
    return *this;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator_ * rhs.denominator_ < rhs.numerator_ * lhs.denominator_;
}

std::ostream& operator<<(std::ostream& out, const Rational& value) {
    out << value.numerator_;
    if (value.denominator_ != 1) {
        out << '/' << value.denominator_;
    }
    return out;
}

}
