#ifndef KURO_TOOL_HPP
#define KURO_TOOL_HPP 1

namespace kuro {

template<typename T>
bool chmin(T& x, const T& y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}

template<typename T>
bool chmax(T& x, const T& y) {
  if (x < y) {
    x = y;
    return true;
  }
  return false;
}

template<typename T>
vector<T> compress(vector<T> v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  return v;
}

template<typename T>
map<T, int> dict(const vector<T> &v) {
  map<T, int> res;
  for(int i = 0; i < (int)v.size(); ++i) {
    res[v[i]] = i;
  }
  return res;
}

} // namespace kuro
#endif  // KURO_TOOL_HPP