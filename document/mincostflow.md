# Min Cost Flow (b-フロー)

一般的な最小費用流問題を解くライブラリです．最小費用b-フロー問題と呼ばれることもあります．フローを水の流れで例えると次のようになります．

有向グラフ $G$ について

- 頂点 $v$ で超過している水量 $b_v$ ($b_v < 0$ ならば不足)
- 辺 $e$ の容量 $\mathrm{cost}_e$ とコスト $\mathrm{cost}_e$

が定まっているとします．辺 $e$ を使って $x$ の量だけ水を移すときに $0 \le x \le \mathrm{cost}_e$ を満たす必要があり，$x \cdot \mathrm{cost}_e$ のコストがかかります．水の過不足を解消するための最小コストを求めます．

以下，頂点番号と辺番号とを区別するために，それぞれの型を `V_id`，`E_id` と表します．どちらも実体は `int` です．

## コンストラクタ

```cpp
(1) MinCostFlow<Cap, Cost> graph()
(2) MinCostFlow<Cap, Cost> graph(V_id n)
```

- (1): $0$ 頂点 $0$ 辺のグラフを作ります．`Cap` は容量の型，`Cost` はコストの型です．
- (2): $n$ 頂点 $0$ 辺のグラフを作ります．`Cap` は容量の型，`Cost` はコストの型です．

**制約**

- $0 \leq n \leq 10^8$
- `Cap, Cost` は `int / int64_t`

**計算量**

- $O(n)$

## add_vertex

```cpp
(1) V_id graph.add_vertex()
(2) vector<V_id> graph.add_vertices(V_id size)
```

頂点を追加します．何番目に追加された頂点かを返します．

- (1): 頂点を $1$ 個追加します．
- (2): 頂点を `size` 個追加します．

**制約**

$n$ を追加前の頂点数として

- (1) $0 \leq n + 1 \leq 10^8$

- (2): $0 \leq \mathrm{size}, 0 \leq n + \mathrm{size} \leq 10^8$

**計算量**

- (1): $O(1)$
- (2): $O(\mathrm{size})$

## add_edge

```cpp
(1) E_id graph.add_edge(V_id from, V_id to, Cap cap, Cost cost)
(2) E_id graph.add_edge(V_id from, V_id to, Cap lower, Cap upper, Cost cost)
```

辺を追加します．何番目に追加された辺かを返します．

- (1): `from` から `to` へ最大容量 `cap`, コスト `cost` の辺を追加します．
- (2): `from` から `to` へ最小流量 `lower`，最大容量 `upper`, コスト `cost` の辺を追加します．

**制約**

$n$ を頂点数として

- $0 \leq \mathrm{from}, \mathrm{to} \lt n$
- (1): $0 \leq \mathrm{cap}$
- (2): $0 \leq \mathrm{lower} \leq \mathrm{upper}$

**計算量**

- $O(1)$

## solve

```cpp
pair<Cap, Cost> graph.solve()
```

水量の過不足を解消する方向にフローを流し，`.first` に解消できたかどうかを，`.second` にコストを入れて返します．

$n$ を頂点数， $m$ を辺数として

**制約**

- $\displaystyle \sum b_v = 0$

- 流したフローの総流量が `Cap` に収まる
- 流したフローのコストの総和が `Cost` に収まる

$d_\mathrm{max}$ を辺のコストの最大値として

- (Cost : `int`): $|nd_\mathrm{max}| \leq 2 \times 10^9 + 1000$
- (Cost : `int64_t`): $|nd_\mathrm{max}| \leq 8 \times 10^{18} + 1000$

**計算量**

$F$ を流量として

- $O(F (n + m) \log (n + m))$

## flow

```cpp
(1) pair<Cap, Cost> graph.flow(V_id s, V_id t)
(2) pair<Cap, Cost> graph.flow(V_id s, V_id t, Cap flow_limit)
```

$s$ から $t$ へ流せるだけ流し，その流量とコストを返します．`.first` に流量，`.second` にコストが入ります．負閉路がある場合，フローの流れ込みの有無にかかわらず循環してコストが減ります．

- (1) $s$ から $t$ へ流せるだけ流します．
- (2) $s$ から $t$ へ流量 `flow_limit` までの範囲で流せるだけ流します．

$n$ を頂点数， $m$ を辺数として

**制約**

`solve` の制約に加えて

- $0 \leq s, t < n$
- $s \neq t$
- すべての頂点で過不足がない
- すべての辺の最小流量を満たすような $s$ から $t$ へのフローが存在する

**計算量**

$F$ を流量として

- $O(F (n + m) \log (n + m))$

## get_edge

```cpp
struct edge<Cap, Cost> {
    V_id from, to;
    Cap cap, flow;
    Cost cost;
};

(1) MinCostFlow<Cap, Cost>::edge graph.get_edge(E_id i)
(2) vector<MinCostFlow<Cap, Cost>::edge> graph.edges()
```

今の内部の辺の状態を返します．辺の順番は `add_edge` で追加された順番と同一です．

- (1): `i` 番目に追加した辺を返します．
- (2): 追加された辺がすべて入った配列を返します．

$m$ を辺数として

**制約**

- (1): $0 \leq i \lt m$

**計算量**

- (1): $O(1)$
- (2): $O(m)$

## private変数，private関数

```cpp
int _n
struct _edge {
  int from
  int to
  int rev
  Cap cap
  Cost cost
}
vector<pair<int, int>> pos
vector<vector<_edge>> g
vector<Cap> b
// others for solve()
```

- `_n` : グラフの頂点数
- `_edge` : グラフの辺
  
  - `from` : 辺の始点
  
  - `to` : 辺の終点
  - `rev` : 逆辺の `g[to]` におけるインデックス
  - `cap` : 容量
  - `cost` : コスト
- `pos` : `pos[i]` は `i+1` 番目に追加された辺の {始点 `from`，`g[from]` におけるインデックス}
- `g` : `g[i]` は始点 `i` の辺の配列
- `b` : `b[i]` は頂点 `i` の水量
- その他 `solve` で使う変数と関数
