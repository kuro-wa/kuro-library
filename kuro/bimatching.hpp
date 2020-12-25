#ifndef KURO_BIMATCHING_HPP
#define KURO_BIMATCHING_HPP 1

namespace kuro {

// Bipertite Matching
struct BiMatching {
 public:
  BiMatching(int n, int m)
    : _n(n), _m(m), g(n), d(n+m, -1) {}
  void add_edge(int u, int v) {
    assert(0 <= u && u < _n);
    assert(0 <= v && v < _m);
    g[u].push_back(_n+v);
  }
  int solve() {
    vector<int> level(_n), used(_n);
    auto bfs = [&]() {
      fill(level.begin(), level.end(), -1);
      queue<int> que;
      for (int i = 0; i < _n; ++i) {
        if (d[i] == -1) {
          level[i] = 0;
          que.push(i);
        }
      }
      while (!que.empty()) {
        int v = que.front(); que.pop();
        for (int u : g[v]) {
          int w = d[u];
          if (w < 0 || level[w] >= 0) continue;
          level[w] = level[v]+1;
          que.push(w);
        }
      }
    };
    auto dfs = [&](auto self, int v)->bool {
      used[v] = 1;
      for (auto& u : g[v]) {
        int w = d[u];
        if (w < 0 || (!used[w] && level[w] > level[v] && self(self, w))) {
          d[v] = u;
          d[u] = v;
          return true;
        }
      }
      return false;
    };
    int flow = 0;
    while (true) {
      bfs();
      fill(used.begin(), used.end(), 0);
      int f = 0;
      for (int i = 0; i < _n; ++i) {
        if (d[i] == -1 && dfs(dfs, i)) ++f;
      }
      if (!f) break;
      flow += f;
    }
    return flow;
  }
  int pair_right(int u) {
    assert(0 <= u && u < _n);
    if (d[u] < 0) return -1;
    return d[u]-_n;
  }
  int pair_left(int v) {
    assert(0 <= v && v < _m);
    return d[_n+v];
  }
 private:
  int _n, _m;
  vector<vector<int>> g;
  vector<int> d;
};

} // namespace kuro
#endif  // KURO_BIMATCHING_HPP