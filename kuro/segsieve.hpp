#ifndef KURO_SEGSIEVE_HPP
#define KURO_SEGSIEVE_HPP 1

namespace kuro {

// Segment Sieve of Erastothenes
struct SegSieve {
 public:
  SegSieve(int64_t a=0, int64_t b=1) : a(a), b(b), f2(b-a) {
    assert(0 <= a && a < b);
    int n = 1;
    while ((int64_t)n*n < b) ++n;
    f.resize(n+1);
    f[0] = f[1] = -1;
    for (int64_t i = 2; i <= n; ++i) {
      if (f[i]) continue;
      f[i] = i;
      for (int64_t j = i*i; j <= n; j += i) {
        if (!f[j]) f[j] = i;
      }
      for (int64_t j = max(i*i, (a+i-1)/i*i); j < b; j += i) {
        if (!f2[j-a]) f2[j-a] = i;
      }
    }
    for (int64_t i = a; i < b; ++i) {
      if (i <= 1) f2[i-a] = -1;
      else if (!f2[i-a]) {
        ps.emplace_back(i);
        f2[i-a] = i;
      }
    }
  }
  vector<int64_t> primes() { return ps;}
  bool is_prime(int64_t x) {
    assert(a <= x && x < b);
    return f2[x-a] == x;
  }
 private:
  int64_t a, b;
  vector<int> f;
  vector<int64_t> f2;
  vector<int64_t> ps;
};

} // namespace kuro
#endif  // KURO_SEGSIEVE_HPP