#ifndef KURO_RSQ_HPP
#define KURO_RSQ_HPP 1
#include <kuro/lazysegtree>

namespace kuro {

// RSQ (Range Sum Query) and RAQ (Range Add Query)
template<typename T, typename F=T>
struct RSQ {
 public:
  RSQ(int n=0) : RSQ(vector<T>(n, T(0))) {}
  RSQ(const vector<T>& v) {
    int n = int(v.size());
    vector<S> w(n);
    for (int i = 0; i < n; ++i) w[i] = S(v[i], 1);
    d = LazySegTree<S, op, e, F, mapping, composition, id>(w);
  }
  void set(int p, T x) { d.set(p, S(x, 1));}
  T get(int p) { return d.get(p).x;}
  T prod(int l, int r) { return d.prod(l, r).x;}
  T all_prod() { return d.all_prod().x;}
  void apply(int p, F f) { d.apply(p, f);}
  void apply(int l, int r, F f) { d.apply(l, r, f);}
 private:
  struct S {
    T x; int l;
    S(T x=T(0), int l=1) : x(x), l(l) {}
  };
  static S op(S a, S b) { return S(a.x+b.x, a.l+b.l);}
  static S e() { return S(T(0), 0);}
  static S mapping(F f, S s) { return S(f*s.l+s.x, s.l);}
  static F composition(F f, F g) { return f+g;}
  static F id() { return F(0);}
  LazySegTree<S, op, e, F, mapping, composition, id> d;
};

} // namespace kuro
#endif  // KURO_RSQ_HPP