#ifndef KURO_SUFFIXARRAY_HPP
#define KURO_SUFFIXARRAY_HPP 1

namespace kuro {

// Suffix Array
template<typename S=string>
struct SuffixArray {
 public:
  SuffixArray(const S& s) : _s(s) {
    int n = _s.size();
    sa.resize(n+1);
    rsa.resize(n+1);
    iota(sa.begin(), sa.end(), 0);
    vector<int> tmp(n+1);
    for (int i = 0; i <= n; ++i) {
      rsa[i] = i < n ? _s[i] : -1;
    }
    for (int len = 1; len < n; len <<= 1) {
      auto cmp = [&](int a, int b) {
        if (rsa[a] != rsa[b]) return rsa[a] < rsa[b];
        int ra = a+len <= n ? rsa[a+len] : -1;
        int rb = b+len <= n ? rsa[b+len] : -1;
        return ra < rb;
      };
      sort(sa.begin(), sa.end(), cmp);
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; ++i) {
        tmp[sa[i]] = tmp[sa[i-1]]+(cmp(sa[i-1], sa[i]) ? 1 : 0);
      }
      swap(rsa, tmp);
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
  vector<int> get_lcp() {
    int n = _s.size();
    vector<int> res(n);
    int h = 0;
    for (int i = 0; i < n; ++i) {
      if (h > 0) --h;
      int j = sa[rsa[i]-1];
      while (i+h < n && j+h < n) {
        if (_s[i+h] != _s[j+h]) break;
        ++h;
      }
      res[rsa[i]-1] = h;
    }
    return res;
  }
 private:
  S _s;
  vector<int> sa, rsa;
};

} // namespace kuro
#endif  // KURO_SUFFIXARRAY_HPP