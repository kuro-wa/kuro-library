#ifndef KURO_TWOSAT_HPP
#define KURO_TWOSAT_HPP 1
#include <kuro/scc>

namespace kuro {

struct TwoSat {
 public:
  TwoSat(int n=0) : _n(n), _answer(n), scc(2*n) {}
  void add_clause(int i, bool f, int j, bool g) {
    assert(0 <= i && i < _n);
    assert(0 <= j && j < _n);
    scc.add_edge(2*i+(f ? 0 : 1), 2*j+(g ? 1 : 0));
    scc.add_edge(2*j+(g ? 0 : 1), 2*i+(f ? 1 : 0));
  }
  bool satisfiable() {
    scc.solve();
    auto ord = scc.order();
    for (int i = 0; i < _n; ++i) {
      if (ord[2*i] == ord[2*i+1]) return false;
      _answer[i] = (ord[2*i] < ord[2*i+1]);
    }
    return true;
  }
  vector<bool> answer() { return _answer;}
 private:
  int _n;
  vector<bool> _answer;
  SCC scc;
};

} // namespace kuro
#endif  // KURO_TWOSAT_HPP