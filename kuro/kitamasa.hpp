#ifndef KURO_KITAMASA_HPP
#define KURO_KITAMASA_HPP 1

namespace kuro {

template<typename T> T _zero() { return T(0);}
template<typename T> T _one() { return T(1);}

// Kitamasa Method
template<typename T, T (*zero)()=_zero<T>, T (*one)()=_one<T>>
struct Kitamasa {
 public:
  Kitamasa(const vector<T>& v) : m(v.size()), cs(v), rs(1) {
    assert((int)v.size() >= 1);
    rs[0] = vector<T>(2*m+1, zero());
    rs[0][1] = one();
  }
  T solve(const vector<T>& a, int64_t n) {
    assert((int)a.size() == m && n >= 0);
    vector<T> res(rs[0]);
    for (int i = 0; n; ++i, n >>= 1) {
      if (i >= (int)rs.size()) {
        rs.emplace_back(merge(rs[i-1], rs[i-1]));
      }
      if (n&1) res = merge(res, rs[i]);
    }
    T ans = zero();
    for (int i = 1; i <= m; ++i) ans = ans+(res[i]*a[i-1]);
    return ans;
  }
 private:
  int m;
  vector<T> cs;
  vector<vector<T>> rs;
  vector<T> merge(const vector<T>& xs, const vector<T>& ys) {
    vector<T> zs(2*m+1, zero());
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= m; ++j) {
        zs[i+j] = zs[i+j]+(xs[i]*ys[j]);
      }
    }
    for (int i = 2*m; i > m; zs[i--] = zero()) {
      for (int j = 1; j <= m; ++j) {
        zs[i-j] = zs[i-j]+(cs[m-j]*zs[i]);
      }
    }
    return zs;
  }
};

} // namespace kuro
#endif  // KURO_KITAMASA_HPP