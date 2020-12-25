#ifndef KURO_MARATHON_HPP
#define KURO_MARATHON_HPP 1

namespace kuro {

// Timer (milli second)
double get_time() {
  static double START_TIME = -1.0;  
  using namespace std::chrono;
  double ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  if (START_TIME < 0.0) START_TIME = ms;
  return ms-START_TIME;
}

// Random number generator
struct RandGenerator {
 public:
  RandGenerator(uint32_t seed=3141592653ul) : val(seed) {}
  uint32_t gen() {
    val ^= val << 13;
    val ^= val >> 17;
    val ^= val << 15;
    return val;
  }
  double gen_double() { return (double)gen()/4294967295.0;}
  uint32_t gen_mod(uint32_t mod) { return gen()%mod;}
  uint32_t gen_range(uint32_t l, uint32_t r) { return l+gen()%(r-l);}
  bool gen_bool(double x) { return (double)gen()/4294967295.0 < x;}
  template<typename T> void shuffle(vector<T>& a) {
    for (int i = a.size()-1; i >= 1; --i) swap(a[i], a[gen()%(i+1)]);
  }
 private:
  uint32_t val;
};

// 1000 separator
template<typename T>
string sep1000(T a) {
  string s = to_string(a), res;
  int n = s.size(), q = n/3, r = n%3;
  res += s.substr(0, r);
  for (int i = 0; i < q; ++i) {
    if (res.size()) res += '\'';
    res += s.substr(i*3+r, 3);
  }
  return res;
}

} // namespace kuro
#endif  // KURO_MARATHON_HPP