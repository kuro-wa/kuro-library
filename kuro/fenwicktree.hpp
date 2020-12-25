#ifndef KURO_FENWICKTREE_HPP
#define KURO_FENWICKTREE_HPP 1

namespace kuro {

// Fenwick Tree (Binary Indexed Tree)
template<typename T>
struct FenwickTree {
 public:
  FenwickTree(int n=0) : _n(n), d(n) {}
  void add(int p, T x) {
    assert(0 <= p && p < _n);
    for (++p; p <= _n; p += p&-p) {
      d[p-1] += x;
    }
  }
  T sum(int r) {
    T res = 0;
    for (; r; r -= r&-r) {
      res += d[r-1];
    }
    return res;
  }
  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    return sum(r)-sum(l);
  }
 private:
  int _n;
  vector<T> d;
};

} // namespace kuro
#endif  // KURO_FENWICKTREE_HPP