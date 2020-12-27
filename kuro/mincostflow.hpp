#ifndef KURO_MINCOSTFLOW_HPP
#define KURO_MINCOSTFLOW_HPP 1

namespace kuro {

// Min Cost Flow
template<typename Cap, typename Cost>
struct MinCostFlow {
  using V_id = int;
  using E_id = int;
 public:
  MinCostFlow(V_id n=0) : _n(0) {
    add_vertices(n);
  }
  V_id add_vertex() {
    ++_n;
    g.resize(_n);
    b.resize(_n);
    return _n-1;
  }
  vector<V_id> add_vertices(V_id size) {
    assert(0 <= size);
    vector<V_id> res(size);
    iota(res.begin(), res.end(), _n);
    _n += size;
    g.resize(_n);
    b.resize(_n);
    return res;
  }
  E_id add_edge(V_id from, V_id to, Cap cap, Cost cost) {
    return add_edge(from, to, 0, cap, cost);
  }
  E_id add_edge(V_id from, V_id to, Cap lower, Cap upper, Cost cost) {
    assert(0 <= from && from < _n);
    assert(0 <= to && to < _n);
    assert(0 <= lower && lower <= upper);
    E_id m = pos.size();
    pos.emplace_back(from, g[from].size());
    V_id from_id = g[from].size();
    V_id to_id = g[to].size();
    if (from == to) ++to_id;
    g[from].emplace_back(_edge{from, to, to_id, upper, cost});
    g[to].emplace_back(_edge{to, from, from_id, -lower, -cost});
    return m;
  }
  void add_supply(V_id v, Cap amount) {b[v] += amount;}
  void add_demand(V_id v, Cap amount) {b[v] -= amount;}
  struct edge { V_id from, to; Cap cap, flow; Cost cost;};
  edge get_edge(E_id i) {
    E_id m = pos.size();
    assert(0 <= i && i < m);
    _edge& e = g[pos[i].first][pos[i].second];
    _edge& re = g[e.to][e.rev];
    return edge{e.from, e.to, e.cap+re.cap, re.cap, e.cost};
  }
  vector<edge> edges() {
    E_id m = pos.size();
    vector<edge> res(m);
    for (E_id i = 0; i < m; ++i) {
      res[i] = get_edge(i);
    }
    return res;
  }
  pair<bool, Cost> solve() {
    potential.resize(_n);
    for (V_id v = 0; v < _n; ++v) for (_edge& e : g[v]) {
      Cost flow = e.cap;
      Cost cost = e.cost-potential[e.to]+potential[e.from];
      if (cost < 0 || flow < 0) {
        e.cap -= flow;
        g[e.to][e.rev].cap += flow;
        b[e.from] -= flow;
        b[e.to] += flow;
      }
    }
    for (V_id v = 0; v < _n; ++v) if (b[v] != 0) {
      (b[v] > 0 ? excess_vs : deficit_vs).emplace_back(v);
    }
    while (dual_ref()) primal();
    Cost cost = 0;
    for (edge& e : edges()) {
      cost += e.flow*e.cost;
    }
    bool success = (excess_vs.empty() && deficit_vs.empty());
    return {success, cost};
  }
  pair<Cap, Cost> flow(V_id s, V_id t, Cap flow_limit=numeric_limits<Cap>::max()) {
    add_supply(s, flow_limit);
    add_demand(t, flow_limit);
    Cost cost = solve().second;
    Cap flow = flow_limit-b[s];
    b[s] = b[t] = 0;
    return {flow, cost};
  }
 private:
  V_id _n;
  struct _edge { V_id from, to; E_id rev; Cap cap; Cost cost;};
  vector<pair<V_id, E_id>> pos;
  vector<vector<_edge>> g;
  vector<Cap> b;
  static Cost constexpr cost_inf = numeric_limits<Cost>::max();
  Cost farthest;
  vector<Cost> potential;
  vector<Cost> dist;
  vector<_edge*> parent;
  vector<V_id> excess_vs, deficit_vs;
  bool dual_ref() {
    dist.assign(_n, cost_inf);
    parent.assign(_n, nullptr);
    excess_vs.erase(remove_if(excess_vs.begin(), excess_vs.end(),
                              [&](V_id v) { return b[v] <= 0;}),
                    excess_vs.end());
    deficit_vs.erase(remove_if(deficit_vs.begin(), deficit_vs.end(),
                              [&](V_id v) { return b[v] >= 0;}),
                    deficit_vs.end());
    priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<pair<Cost, int>>> que;
    for (V_id v : excess_vs) que.emplace(dist[v] = 0, v);
    farthest = 0;
    size_t deficit_count = 0;
    while (!que.empty()){
      auto [d, v] = que.top(); que.pop();
      if (dist[v] < d) continue;
      farthest = d;
      if (b[v] < 0) ++deficit_count;
      if (deficit_count >= deficit_vs.size()) break;
      for (_edge& e : g[v]) {
        if (e.cap <= 0) continue;
        Cost cost = e.cost-potential[e.to]+potential[e.from];
        if (dist[e.to]-d <= cost) continue;
        dist[e.to] = d+cost;
        parent[e.to] = &e;
        que.emplace(dist[e.to] = d+cost, e.to);
      }
    }
    for (V_id v = 0; v < _n; ++v) {
      potential[v] += min(dist[v], farthest);
    }
    return deficit_count > 0;
  }
  void primal() {
    for (V_id t : deficit_vs) {
      if (dist[t] > farthest) continue;
      Cap flow = -b[t];
      V_id v;
      for (v = t; parent[v] != nullptr; v = parent[v]->from) {
        flow = min(flow, parent[v]->cap);
      }
      flow = min(flow, b[v]);
      if (flow <= 0) continue;
      for (v = t; parent[v] != nullptr;) {
        _edge& e = *parent[v];
        e.cap -= flow;
        g[e.to][e.rev].cap += flow;
        V_id pv = e.from;
        if (e.cap <= 0) parent[v] = nullptr;
        v = pv;
      }
      b[t] += flow;
      b[v] -= flow;
    }
  }
};

} // namespace kuro
#endif  // KURO_MINCOSTFLOW_HPP