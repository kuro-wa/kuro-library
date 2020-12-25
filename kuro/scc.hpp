#ifndef KURO_SCC_HPP
#define KURO_SCC_HPP 1

namespace kuro {

// Decomposition of SCC (Strongly Connected Component)
struct SCC {
 public:
  SCC(int n=0) : _n(n) {}
  void add_edge(int from, int to) {
    assert(0 <= from && from < _n);
    assert(0 <= to && to < _n);
    edges.push_back({from, {to}});
  }
  vector<vector<int>> solve() {
    int group_num = scc_ids();
    vector<int> counts(group_num);
    for (auto x : ids) ++counts[x];
    groups.assign(group_num, vector<int>());
    for (int i = 0; i < group_num; ++i) {
      groups[i].reserve(counts[i]);
    }
    for (int i = 0; i < _n; ++i) {
      groups[ids[i]].emplace_back(i);
    }
    return groups;
  }
  vector<int> order() {
    return ids;
  }
 private:
  int _n;
  struct edge { int to;};
  vector<pair<int, edge>> edges;
  vector<int> ids;
  vector<vector<int>> groups;
  template<typename E> struct csr {
    vector<int> start;
    vector<E> elist;
    csr(int n, const vector<pair<int, E>>& edges)
      : start(n+1), elist(edges.size()) {
      for (auto& e : edges) {
        ++start[e.first+1];
      }
      for (int i = 1; i <= n; ++i) {
        start[i] += start[i-1];
      }
      auto counter = start;
      for (auto& e : edges) {
        elist[counter[e.first]++] = e.second;
      }
    }
  };
  int scc_ids() {
    auto g = csr<edge>(_n, edges);
    int now_ord = 0, group_num = 0;
    vector<int> visited, low(_n), ord(_n, -1);
    ids.assign(_n, 0);
    visited.reserve(_n);
    auto dfs = [&](auto self, int v)->void {
      low[v] = ord[v] = now_ord++;
      visited.emplace_back(v);
      for (int i = g.start[v]; i < g.start[v+1]; ++i) {
        int to = g.elist[i].to;
        if (ord[to] == -1) {
          self(self, to);
          low[v] = min(low[v], low[to]);
        }
        else {
          low[v] = min(low[v], ord[to]);
        }
      }
      if (low[v] == ord[v]) {
        while (true) {
          int u = visited.back();
          visited.pop_back();
          ord[u] = _n;
          ids[u] = group_num;
          if (u == v) break;
        }
        ++group_num;
      }
    };
    for (int i = 0; i < _n; ++i) {
      if (ord[i] == -1) dfs(dfs, i);
    }
    for (int& x : ids) {
      x = group_num-1-x;
    }
    return group_num;
  }
};

} // namespace kuro
#endif  // KURO_SCC_HPP