#ifndef KURO_SUFFIXARRAY_HPP
#define KURO_SUFFIXARRAY_HPP 1

namespace kuro {

// Suffix Array
template<typename S=string>
struct SuffixArray {
 public:
  SuffixArray(const S& s) : _s(s) {
    int n = s.size();
    sa.resize(n+1);
    iota(sa.begin(), sa.end(), 0);
    vector<int> rnk(n+1), tmp(n+1);
    for (int i = 0; i <= n; ++i) {
      rnk[i] = i < n ? s[i] : -1;
    }
    for (int len = 1; len < n; len <<= 1) {
      auto cmp = [&](int a, int b) {
        if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
        int ra = a+len <= n ? rnk[a+len] : -1;
        int rb = b+len <= n ? rnk[b+len] : -1;
        return ra < rb;
      };
      sort(sa.begin(), sa.end(), cmp);
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; ++i) {
        tmp[sa[i]] = tmp[sa[i-1]]+(cmp(sa[i-1], sa[i]) ? 1 : 0);
      }
      swap(rnk, tmp);
    }
  }
  int operator[](int i) const { return sa[i];}
  int lower_bound(S t) {
    assert(t.size());
    auto cmp = [&](int si) {
      int sl = _s.size(), tl = t.size(), ti = 0;
      while (si < sl && ti < tl) {
        string c = _s.substr(si, 1);
        if (_s[si] < t[ti]) return true;
        if (_s[si] > t[ti]) return false;
        ++si; ++ti;
      }
      return si == sl && ti < tl;
    };
    int l = 0, r = sa.size();
    while (r-l > 1) {
      int c = (l+r)>>1;
      if (cmp(sa[c])) l = c;
      else r = c;
    }
    return r;
  }
  int upper_bound(S t) {
    assert(t.size());
    auto cmp = [&](int si) {
      int sl = _s.size(), tl = t.size(), ti = 0;
      while (si < sl && ti < tl) {
        if (_s[si] < t[ti]) return true;
        if (_s[si] > t[ti]) return false;
        ++si; ++ti;
      }
      return si == sl || ti == tl;
    };
    int l = 0, r = sa.size();
    while (r-l > 1) {
      int c = (l+r)>>1;
      if (cmp(sa[c])) l = c;
      else r = c;
    }
    return r;
  }
  int count(S t) {
    return upper_bound(t)-lower_bound(t);
  }
 private:
  S _s;
  vector<int> sa;
};

} // namespace kuro
#endif  // KURO_SUFFIXARRAY_HPP