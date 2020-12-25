#ifndef KURO_MODINT_HPP
#define KURO_MODINT_HPP 1

namespace kuro {

// Static Mod int
template <int m, bool prime=false>
struct StaticModint {
  using mint = StaticModint;
 public:
  static int mod() { return (int)_m;}
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }
  StaticModint(int64_t v=0) {
    _v = normalize(v);
  }
  int val() const { return (int)_v;}
  mint& operator++() { if (++_v == _m) _v = 0; return *this;}
  mint& operator--() { if (_v-- == 0) _v = _m-1; return *this;}
  mint operator++(int) { mint res = *this; ++*this; return res;}
  mint operator--(int) { mint res = *this; --*this; return res;}
  mint& operator+=(const mint& rhs) {
    if ((_v += rhs._v) >= _m) _v -= _m;
    return *this;
  }
  mint& operator-=(const mint& rhs) {
    if ((_v -= rhs._v) >= _m) _v += _m;
    return *this;
  }
  mint& operator*=(const mint& rhs) {
    _v = (uint32_t)((uint64_t)_v*rhs._v%_m);
    return *this;
  }
  mint& operator/=(const mint& rhs) { return *this *= rhs.inv();}
  mint operator+() const { return *this;}
  mint operator-() const { return mint()-*this;}
  mint pow(int64_t n) const {
    assert(n >= 0);
    mint x = *this, res = 1;
    while (n) {
      if (n&1) res *= x;
      x *= x;
      n >>= 1;
    }
    return res;
  }
  mint inv() const {
    if (prime) {
      return pow(_m-2);
    }
    else {
      int a = _v, b = _m;
      int x = 1, u = 0;
      while (b) {
        int t = a/b;
        a -= t*b; swap(a, b);
        x -= t*u; swap(x, u);
      }
      assert(a == 1);
      return mint(x);
    }
  }
  friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
  friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
  friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
  friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
  friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
  friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
  friend bool operator<(const mint& lhs, const mint& rhs) { return lhs._v < rhs._v;}
  friend istream& operator>>(istream& is, mint& a) {
    int64_t v;
    is >> v;
    a._v = normalize(v);
    return is;
  }
  friend ostream& operator<<(ostream& os, const mint& a) { return os << a._v;}
  template <typename T> explicit operator T() const { return static_cast<T>(_v); }
 private:
  uint32_t _v;
  static constexpr uint32_t _m = (uint32_t)m;
  static uint32_t normalize(int64_t v) {
    int64_t x = v%(int64_t)_m;
    if (x < 0) x += _m;
    return (uint32_t)x;
  }
};

// Dynamic Mod int
template <int id, bool prime=false>
struct DynamicModint {
  using mint = DynamicModint;
 public:
  static int mod() { return (int)_m;}
  static void set_mod(int m) {
    assert(m >= 1);
    _m = m;
  }
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }
  DynamicModint(int64_t v=0) {
    _v = normalize(v);
  }
  int val() const { return (int)_v;}
  mint& operator++() { if (++_v == _m) _v = 0; return *this;}
  mint& operator--() { if (_v-- == 0) _v = _m-1; return *this;}
  mint operator++(int) { mint res = *this; ++*this; return res;}
  mint operator--(int) { mint res = *this; --*this; return res;}
  mint& operator+=(const mint& rhs) {
    if ((_v += rhs._v) >= _m) _v -= _m;
    return *this;
  }
  mint& operator-=(const mint& rhs) {
    if ((_v -= rhs._v) >= _m) _v += _m;
    return *this;
  }
  mint& operator*=(const mint& rhs) {
    _v = (uint32_t)((uint64_t)_v*rhs._v%_m);
    return *this;
  }
  mint& operator/=(const mint& rhs) { return *this *= rhs.inv();}
  mint operator+() const { return *this;}
  mint operator-() const { return mint()-*this;}
  mint pow(int64_t n) const {
    assert(n >= 0);
    mint x = *this, res = 1;
    while (n) {
      if (n&1) res *= x;
      x *= x;
      n >>= 1;
    }
    return res;
  }
  mint inv() const {
    if (prime) {
      return pow(_m-2);
    }
    else {
      int a = _v, b = _m;
      int x = 1, u = 0;
      while (b) {
        int t = a/b;
        a -= t*b; swap(a, b);
        x -= t*u; swap(x, u);
      }
      assert(a == 1);
      return mint(x);
    }
  }
  friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
  friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
  friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
  friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
  friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
  friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
  friend bool operator<(const mint& lhs, const mint& rhs) { return lhs._v < rhs._v;}
  friend istream& operator>>(istream& is, mint& a) {
    int64_t v;
    is >> v;
    a._v = normalize(v);
    return is;
  }
  friend ostream& operator<<(ostream& os, const mint& a) { return os << a._v;}
  template <typename T> explicit operator T() const { return static_cast<T>(_v); }
 private:
  uint32_t _v;
  static uint32_t _m;
  static uint32_t normalize(int64_t v) {
    int64_t x = v%(int64_t)_m;
    if (x < 0) x += _m;
    return (uint32_t)x;
  }
};
template<int id, bool prime> uint32_t DynamicModint<id, prime>::_m = 998244353;

using modint1000000007 = StaticModint<1000000007, true>;
using modint998244353 = StaticModint<998244353, true>;
// hoge
using modint = DynamicModint<-1>;

} // namespace kuro
#endif  // KURO_MODINT_HPP