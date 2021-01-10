#ifndef KURO_SEGTREE_HPP
#define KURO_SEGTREE_HPP 1

namespace kuro {

// Segment Tree
template<typename S, S (*op)(S, S), S(*e)()>
struct SegTree {
 public:
  SegTree(int n_=0) : SegTree(vector<S>(n_, e())) {}
  SegTree(const vector<S>& v) : n(int(v.size())) {
    size = 1;
    while (size < n) size <<= 1;
    d = vector<S>(2*size, e());
    for (int i = 0; i < n; ++i) d[size+i] = v[i];
    for (int i = size-1; i >= 1; --i) {
      update(i);
    }
  }
  S get(int p) {
    assert(0 <= p && p < n);
    return d[p+size];
  }
  void set(int p, S x) {
    assert(0 <= p && p < n);
    d[p += size] = x;
    while (p >>= 1) update(p);
  }
  void add(int p, S x) {
    assert(0 <= p && p < n);
    set(p, op(get(p), x));
  }
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    S sml = e(), smr = e();
    l += size;
    r += size;
    while (l < r) {
      if (l&1) sml = op(sml, d[l++]);
      if (r&1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }
  S all_prod() { return d[1];}
  template<bool (*f)(S)> int max_right(int l) {
    return max_right(l, [](S x) { return f(x);});
  }
  template<typename F> int max_right(int l, F f) {
    assert(0 <= l && l <= n);
    assert(f(e()));
    if (l == n) return n;
    l += size;
    S sm = e();
    do {
      while (~l&1) l >>= 1;
      if (!f(op(sm, d[l]))) {
        while (l < size) {
          l <<= 1;
          if (f(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            ++l;
          }
        }
        return l-size;
      }
      sm = op(sm, d[l]);
      ++l;
    } while ((l&-l) != l);
    return n;
  }
  template<bool (*f)(S)> int min_left(int r) {
    return min_left(r, [](S x) { return f(x);});
  }
  template<typename F> int min_left(int r, F f) {
    assert(0 <= r && r <= n);
    assert(f(e()));
    if (r == 0) return 0;
    r += size;
    S sm = e();
    do {
      --r;
      while (r > 1 && (r&1)) r >>= 1;
      if (!f(op(d[r], sm))) {
        while (r < size) {
          r = (r<<1)+1;
          if (f(op(d[r], sm))) {
            sm = op(d[r], sm);
            --r;
          }
        }
        return r+1-size;
      }
      sm = op(d[r], sm);
    } while((r&-r) != r);
    return 0;
  }
 private:  
  int n, size;
  vector<S> d;
  void update(int k) { d[k] = op(d[2*k], d[2*k+1]);}
};

} // namespace kuro
#endif  // KURO_SEGTREE_HPP