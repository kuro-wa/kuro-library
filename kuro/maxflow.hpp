#ifndef KURO_MAXFLOW_HPP
#define KURO_MAXFLOW_HPP 1

namespace kuro {

// Max Flow
template<typename Cap>
struct MaxFlow {
 public:
  MaxFlow(int n=0) : _n(0) {
    add_vertices(n);
  }
  int add_vertex() {
    ++_n;
    g.resize(_n);
    return _n-1;
  }
  vector<int> add_vertices(int size) {
    assert(size >= 0);
    vector<int> res(size);
    iota(res.begin(), res.end(), _n);
    _n += size;
    g.resize(_n);
    return res;
  }
  int add_edge(int from, int to, Cap cap) {
    assert(0 <= from && from < _n);
    assert(0 <= to && to < _n);
    assert(0 <= cap);
    int m = (int)pos.size();
    pos.emplace_back(from, (int)g[from].size());
    int from_id = (int)g[from].size();
    int to_id = (int)g[to].size();
    if (from == to) ++to_id;
    g[from].push_back(_edge{to, to_id, cap});
    g[to].push_back(_edge{from, from_id, 0});
    return m;
  }
  Cap flow(int s, int t, Cap flow_limit=numeric_limits<Cap>::max()) {
    assert(0 <= s && s < _n);
    assert(0 <= t && t < _n);
    assert(s != t);
    vector<int> level(_n), iter(_n);
    auto bfs = [&]() {
      fill(level.begin(), level.end(), -1);
      queue<int> que;
      level[s] = 0;
      que.emplace(s);
      while (!que.empty()) {
        int v = que.front(); que.pop();
        for (_edge& e : g[v]) {
          if (e.cap == 0 || level[e.to] >= 0) continue;
          level[e.to] = level[v]+1;
          if (e.to ==  t) return;
          que.emplace(e.to);
        }
      }
    };
    auto dfs = [&](auto self, int v, Cap up) {
      if (v == s) return up;
      Cap res = 0;
      int level_v = level[v];
      for (int& i = iter[v]; i < (int)g[v].size(); ++i) {
        _edge& e = g[v][i];
        if (level_v <= level[e.to]) continue;
        if (g[e.to][e.rev].cap == 0) continue;
        Cap d = self(self, e.to, min(up-res, g[e.to][e.rev].cap));
        if (d <= 0) continue;
        g[v][i].cap += d;
        g[e.to][e.rev].cap -= d;
        res += d;
        if (res == up) return res;
      }
      level[v] = _n;
      return res;
    };
    Cap flow = 0;
    while (flow < flow_limit) {
      bfs();
      if (level[t] == -1) break;
      fill(iter.begin(), iter.end(), 0);
      Cap f = dfs(dfs, t, flow_limit-flow);
      if (!f) break;
      flow += f;
    }
    return flow;
  }
 private:
  int _n;
  struct _edge { int to, rev; Cap cap;};
  vector<pair<int, int>> pos;
  vector<vector<_edge>> g;
};

} // namespace kuro
#endif  // KURO_MAXFLOW_HPP