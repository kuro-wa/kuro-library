#ifndef KURO_SIEVE_HPP
#define KURO_SIEVE_HPP 1

namespace kuro {

// Sieve of Eratosthenes
struct Sieve {
 public:
  Sieve(int n=1) : n(n), f(n+1) {
    f[0] = f[1] = -1;
    for (int64_t i = 2; i <= n; ++i) {
      if (f[i]) continue;
      ps.emplace_back(i);
      f[i] = i;
      for (int64_t j = i*i; j <= n; j += i) {
        if (!f[j]) f[j] = i;
      }
    }
  }
  vector<int> primes() { return ps;}
  bool is_prime(int x) {
    assert(0 <= x && x <= n);
    return f[x] == x;
  }
  bool is_prime(int64_t x) {
    assert(0 <= x && x <= (int64_t)n*n);
    for (int p : ps) {
      if ((int64_t)p*p > x) break;
      if (x%p == 0) return false;
    }
    return x != 1;
  }
  map<int, int> factor(int x) {
    assert(0 <= x && x <= n);
    vector<int> fl = factor_list(x);
    if (fl.size() == 0) return {};
    map<int, int> res;
    for (int p : fl) ++res[p];
    return res;
  }
  map<int64_t,int> factor(int64_t x) {
    assert(0 <= x && x <= (int64_t)n*n);
    map<int64_t,int> res;
    for (int p : ps) {
      int y = 0;
      while (x%p == 0) x /= p, ++y;
      if (y != 0) res[p] = y;
    }
    if (x != 1) res[x] =1;
    return res;
  }
 private:
  int n;
  vector<int> f;
  vector<int> ps;
  vector<int> factor_list(int x) {
    vector<int> res;
    while (x != 1) {
      res.emplace_back(f[x]);
      x /= f[x];
    }
    return res;
  }
};

} // namespace kuro
#endif  // KURO_SIEVE_HPP