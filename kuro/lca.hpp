#ifndef KURO_LCA_HPP
#define KURO_LCA_HPP 1

namespace kuro {

// Lowest Common Ancestor
template<typename Cost=char>
struct LCA {
 public:
  LCA(int n) : _n(n), g(n), par(n), depths(n), dists(n) {
    log = 0;
    while ((1<<log) < _n) ++log;
    par.assign(log, vector<int>(_n+1, _n));
  }
  void add_edge(int u, int v, Cost cost=0) {
    g[u].emplace_back(edge{v, cost});
    g[v].emplace_back(edge{u, cost});
  }
  void init(int root=0) {
    _root = root;
    dfs(root, _n, 0, 0);
    for (int i = 1; i < log; ++i) {
      for (int j = 0; j < _n; ++j) {
        par[i][j] = par[i-1][par[i-1][j]];
      }
    }
  }
  int query(int u, int v) {
    if (depths[u] < depths[v]) swap(u, v);
    int gap = depths[u]-depths[v];
    for (int i = log-1; i >= 0; --i) {
      if (gap>>i&1) u = par[i][u];
    }
    if (u == v) return u;
    for (int i = log-1; i >= 0; --i) {
      if (par[i][u] != par[i][v]) {
        u = par[i][u];
        v = par[i][v];
      }
    }
    return par[0][u];
  }
  int length(int u, int v=-1) {
    if (v == -1) v = _root;
    return depths[u]+depths[v]-depths[query(u, v)]*2;
  }
  Cost dist(int u, int v=-1) {
    if (v == -1) v = _root;
    return dists[u]+dists[v]-dists[query(u, v)]*2;
  }
  int up(int v, int l) {
    for (int i = log-1; i >= 0; --i) {
      if (l>>i&1) v = par[i][v];
    }
    if (v == _n) v = -1;
    return v;
  }
 private:
  int _n, _root, log;
  struct edge { int to; Cost cost;};
  vector<vector<edge>> g;
  vector<vector<int>> par;
  vector<int> depths;
  vector<Cost> dists;
  void dfs(int v, int p, int d, Cost c) {
    par[0][v] = p;
    depths[v] = d;
    dists[v] = c;
    for (edge& e : g[v]) {
      if (e.to == p) continue;
      dfs(e.to, v, d+1, c+e.cost);
    }
  }
};

} // namespace kuro
#endif  // KURO_LCA_HPP