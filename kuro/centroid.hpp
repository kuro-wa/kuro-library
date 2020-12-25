#ifndef KURO_CENTROID_HPP
#define KURO_CENTROID_HPP 1

namespace kuro {

// Centroid Decomposition
struct Centroid{
 public:
  Centroid(int n) : _n(n), size(n, 1), used(n, 0), g(n) {}
  void add_edge(int u, int v) {
    assert(0 <= u && u < _n);
    assert(0 <= v && v < _n);
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  vector<int> solve(int v) {
    assert(0 <= v && v < _n);
    int sz = dfs_size(v, -1);
    vector<int> cs;
    dfs_centroid(v, -1, sz, cs);
    return cs;
  }
  void disable(int v) {
    assert(0 <= v && v < _n);
    used[v] = 1;
  }
  void enable(int v) {
    assert(0 <= v && v < _n);
    used[v] = 0;
  }
  bool alive(int v) {
    assert(0 <= v && v < _n);
    return !used[v];
  }
 private:
  int _n;
  vector<int> size;
  vector<char> used;
  vector<vector<int>> g;
  int dfs_size(int v, int p) {
    size[v] = 1;
    for(int to : g[v]) {
      if (to == p || used[to]) continue;
      size[v] += dfs_size(to, v);
    }
    return size[v];
  }
  void dfs_centroid(int v, int p, int sz, vector<int> &cs) {
    bool ok = true;
    for (int to : g[v]){
      if(to == p || used[to]) continue;
      dfs_centroid(to, v, sz, cs);
      ok &= (size[to] <= sz/2);
    }
    ok &= (sz-size[v] <= sz/2);
    if (ok) cs.emplace_back(v);
  }
};

} // namespace kuro
#endif  // KURO_CENTROID_HPP