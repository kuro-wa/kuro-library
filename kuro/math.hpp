#ifndef KURO_MATH_HPP
#define KURO_MATH_HPP 1

namespace kuro {

// Solves a*x+b*y=gcd(a, b) and returns gcd(a, b)
template<typename T>
T extgcd(T a, T b, T& x, T& y) {
  x = 1, y = 0;
  T u = 0, v = 1;
  while (b) {
    T t = a/b;
    a -= t*b; swap(a, b);
    x -= t*u; swap(x, u);
    y -= t*v; swap(y, v);
  }
  if (a < 0) x *= -1, y *= -1, a *= -1;
  return a;
}

// Enumerate divisors of n
vector<int64_t> divisor(int64_t n) {
  vector<int64_t> res;
  for (int64_t i = 1; i*i <= n; ++i) {
    if (n%i == 0) {
      res.emplace_back(i);
      if(i*i != n) res.emplace_back(n/i);
    }
  }
  sort(res.begin(), res.end());
  return res;
}

// Returns x^n mod(m)
int64_t pow_mod(int64_t x, int64_t n, int64_t m) {
  assert(n >= 0 && m >= 1);
  int64_t res = 1, y = (x%m+m)%m;
  while (n) {
    if (n&1) res = res*y%m;
    y = y*y%m;
    n >>= 1;
  }
  return res;
}

// Returns Moebius function for divisors of n
map<int64_t, int> moebius(int64_t n) {
  map<int64_t, int> res;
  vector<int64_t> primes;
  for (int64_t i = 2; i*i <= n; ++i) {
    if (n%i == 0) {
      primes.emplace_back(i);
      while (n%i == 0) n /= i;
    }
  }
  if (n != 1) primes.emplace_back(n);
  int sz = primes.size();
  for (int bit = 0; bit < (1<<sz); ++bit) {
    int m = 1, d = 1;
    for (int i = 0; i < sz; ++i) {
      if (bit>>i&1) {
        m *= -1;
        d *= primes[i];
      }
    }
    res[d] = m;
  }
  return res;
}

// Returns {y, z} s.t. y%m[i] = r[i], 0 <= y < z := lcm(m[i])
pair<int64_t, int64_t> crt(const vector<int64_t>& r, const vector<int64_t>& m) {
  assert(r.size() == m.size());
  int n = (int)r.size();
  int64_t r0 = 0, m0 = 1;
  for (int i = 0; i < n; ++i) {
    assert(1 <= m[i]);
    int64_t m1 = m[i], r1 = (r[i]%m1+m1)%m1;
    if (m0 < m1) {
      swap(r0, r1);
      swap(m0, m1);
    }
    if (m0%m1 == 0) {
      if (r0%m1 != r1) return {0, 0};
      continue;
    }
    int64_t im, _;
    int64_t g = extgcd(m0, m1, im, _);
    if ((r1-r0)%g != 0) return {0, 0};
    int64_t u1 = m1/g;
    int64_t x = (r1-r0)/g%u1*im%u1;
    r0 += x*m0;
    m0 *= u1;
    if (r0 < 0) r0 += m0;
  }
  return {r0, m0};
}

} // namespace kuro
#endif  // KURO_MATH_HPP