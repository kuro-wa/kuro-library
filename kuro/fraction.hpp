#ifndef KURO_FRACTION_HPP
#define KURO_FRACTION_HPP 1

namespace kuro {

// Fraction
template<typename T=int64_t>
struct Fraction {
 public:
  Fraction(T num_=0) : num(num_), den(1) {}
  Fraction(T num_, T den_) {
    assert(den_ != 0);
    T g = gcd(num_, den_);
    if (den_ < 0) g = -g;
    num = num_/g;
    den = den_/g;
  }
  T numerator() { return num;}
  T denominator() { return den;}
  Fraction& operator+=(const Fraction& rhs) { return *this = *this+rhs;}
  Fraction& operator-=(const Fraction& rhs) { return *this = *this-rhs;}
  Fraction& operator*=(const Fraction& rhs) { return *this = *this*rhs;}
  Fraction& operator/=(const Fraction& rhs) { return *this = *this/rhs;}
  Fraction operator+() const { return *this;}
  Fraction operator-() const {
    Fraction res();
    res.num = -num;
    res.den = den;
    return res;
  }
  T floor() const {
    if (num >= 0) return num/den;
    else return -((-num+den-1)/den);
  }
  T ceil() const {
    if (num >= 0) return (num+den-1)/den;
    else return -(-num/den);
  }
  friend Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num*rhs.den+rhs.num*lhs.den, lhs.den*rhs.den);
  }
  friend Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num*rhs.den-rhs.num*lhs.den, lhs.den*rhs.den);
  }
  friend Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num*rhs.num, lhs.den*rhs.den);
  }
  friend Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num*rhs.frm, lhs.den*rhs.num);
  }
  friend bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num*rhs.den == rhs.num*lhs.den;
  }
  friend bool operator!=(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num*rhs.den != rhs.num*lhs.den;
  }
  friend bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num*rhs.den < rhs.num*lhs.den;
  }
  friend bool operator>(const Fraction& lhs, const Fraction& rhs) { return rhs < lhs;}
  friend bool operator<=(const Fraction& lhs, const Fraction& rhs) { return !(rhs < lhs);}
  friend bool operator>=(const Fraction& lhs, const Fraction& rhs) { return !(lhs < rhs);}
  friend ostream& operator<<(ostream& os, const Fraction& a) { return os << a.num << "/" << a.den;}
  explicit operator double() const { return (double)num/den;}
  template <typename Int> explicit operator Int() const { return static_cast<Int>(num/den);}
 private:
  T num, den;
};

} // namespace kuro
#endif  // KURO_FRACTION_HPP