#ifndef KURO_MODFACTORIAL_HPP
#define KURO_MODFACTORIAL_HPP 1
#include <kuro/modint>

namespace kuro {

// Mod Factorial
template<typename Mint>
struct ModFactorial {
 public:
  ModFactorial(int ub_=2000005) : ub(ub_), facts(ub+1), ifacts(ub+1) {
    facts[0] = 1;
    for (int i = 1; i <= ub; ++i) {
      facts[i] = facts[i-1]*i;
    }
    ifacts[ub] = facts[ub].inv();
    for (int i = ub; i >= 1; --i) {
      ifacts[i-1] = ifacts[i]*i;
    }
  }
  Mint fact(int n) {
    assert(0 <= n && n <= ub);
    return facts[n];
  }
  Mint ifact(int n) {
    assert(0 <= n && n <= ub);
    return ifacts[n];
  }
  Mint comb(int n, int k) {
    assert(0 <= n && n <= ub);
    assert(0 <= k);
    if (n < k) return 0;
    return facts[n]*ifacts[k]*ifacts[n-k];
  }
  Mint perm(int n, int k) {
    assert(0 <= n && n <= ub);
    assert(0 <= k);
    if (n < k) return 0;
    return facts[n]*ifacts[n-k];
  }
  Mint homo(int n, int k) {
    return comb(n+k-1, k);
  }
  Mint multiperm(vector<int> a) {
    Mint res = 1;
    int s = 0;
    for (int x : a) {
      assert(0 <= x && x <= ub);
      s += x;
      res *= ifacts[x];
    }
    assert(s <= ub);
    return res*facts[s];
  }
 private:
  int ub;
  vector<Mint> facts, ifacts;
};

} // namespace kuro
#endif  // KURO_MODFACTORIAL_HPP