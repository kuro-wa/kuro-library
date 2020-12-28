#ifndef KURO_ROLLONGHASH_HPP
#define KURO_ROLLONGHASH_HPP 1

namespace kuro {

using ull = uint64_t;
constexpr ull B998244353 = 998244353;
constexpr ull B1000000007 = 1000000007;

template<ull b=B998244353>
struct RollingHash {
 public:
  RollingHash(string& s) {
    vector<ull> v;
    for (char c : s) v.emplace_back(c);
    init(v);
  }
  template<typename T>
  RollingHash(vector<T>& v) {
    vector<ull> vu;
    for (T x : v) vu.emplace_back((ull)x);
    init(vu);
  }
  RollingHash(vector<ull>& v) { init(v);}
  ull get(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    ull res = hash[r]-hash[l]*powb[r-l];
    return res;
  }
  ull get() { return hash.back();}
 private:
  int n;
  vector<ull> hash, powb;
  void init(vector<ull>& v) {
    n = v.size();
    hash.assign(n+1, 0);
    powb.assign(n+1, 1);
    for (int i = 0; i < n; ++i) {
      hash[i+1] = hash[i]*b+v[i];
      powb[i+1] = powb[i]*b;
    }
  }
};

template<ull br=B998244353, ull bc=B1000000007>
struct RollingHash2D {
 public:
  RollingHash2D(vector<string>& s, int h, int w) {
    vector<vector<ull>> v(s.size());
    for (int i = 0; i < (int)s.size(); ++i) {
      for (char c : s[i]) v[i].emplace_back(c);
    }
    init(v, h, w);
  }
  template<typename T>
  RollingHash2D(vector<vector<T>>& v, int h, int w) {
    vector<vector<ull>> vu(v.size());
    for (int i = 0; i < (int)v.size(); ++i) {
      for (T x : v[i]) vu[i].emplace_back((ull)x);
    }
    init(vu, h, w);
  }
  RollingHash2D(vector<vector<ull>>& v, int h, int w) { init(v, h, w);}
  vector<ull>& operator[](int i) { return hash[i];}
 private:
  int n, m;
  vector<vector<ull>> hash;
  void init(vector<vector<ull>>& v, int h, int w) {
    n = v.size(), m = v[0].size();
    assert(0 <= h && h <= n);
    assert(0 <= w && w <= m);
    hash.assign(n-h+1, vector<ull>(m-w+1));
    vector tmp(m-w+1, vector<ull>(n));
    for (int i = 0; i < n; ++i) {
      RollingHash<br> d(v[i]);
      for (int j = 0; j <= m-w; ++j) {
        tmp[j][i] = d.get(j, j+w);
      }
    }
    for (int j = 0; j <= m-w; ++j) {
      RollingHash<bc> d(tmp[j]);
      for (int i = 0; i <= n-h; ++i) {
        hash[i][j] = d.get(i, i+h);
      }
    }
  }
};

} // namespace kuro
#endif  // KURO_ROLLONGHASH_HPP