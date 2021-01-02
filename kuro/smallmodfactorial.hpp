#ifndef KURO_SMALLMODFACTORIAL_HPP
#define KURO_SMALLMODFACTORIAL_HPP 1

#include <kuro/modint>

namespace kuro {

// Small Mod Factorial
template<typename Mint>
struct SmallModFactorial {
 public:
  SmallModFactorial() : p(Mint::mod()), fact(p) {
    fact[0] = 1;
    for (int i = 1; i < p; ++i) {
      fact[i] = fact[i-1]*i;
    }
  }
  Mint comb(int64_t n, int64_t k) {
    assert(0 <= n && 0 <= k);
    if (n < k) return 0;
    auto [a1, e1] = extract(n);
    auto [a2, e2] = extract(k);
    auto [a3, e3] = extract(n-k);
    if (e1 > e2+e3) return 0;
    return a1/(a2*a3);
  }
 private:
  int p;
  vector<Mint> fact;
  pair<Mint, int64_t> extract(int64_t n) {
    Mint a = 1;
    int64_t e = 0;
    while (n) {
      a *= (n/p&1 ? -fact[n%p] : fact[n%p]);
      e += (n /= p);
    }
    return {a, e};
  }
};

} // namespace kuro
#endif  // KURO_SMALLMODFACTORIAL_HPP