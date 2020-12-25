[TOC]

# Min Cost Flow (2点間)

$2$ 点間の最小費用流問題を解くライブラリです．負閉路を扱うことはできません．

## コンストラクタ

```cpp
(1) MinCostFlow2P<Cap, Cost> graph()
(2) MinCostFlow2P<Cap, Cost> graph(int n)
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
(1) int graph.add_vertex()
(2) vector<int> graph.add_vertices(int size)
```

頂点を追加します．何番目に追加された頂点かを返します．

- (1): 頂点を $1$ 個追加します．
- (2): 頂点を `size` 個追加します．

**制約**

追加前の頂点数を $n$ として

- (1) $0 \leq n + 1 \leq 10^8$

- (2): $0 \leq \mathrm{size}, 0 \leq n + \mathrm{size} \leq 10^8$

**計算量**

- (1): $O(1)$
- (2): $O(\mathrm{size})$

## add_edge

```cpp
int graph.add_edge(int from, int to, Cap cap, Cost cost)
```

`from` から `to` へ最大容量 `cap`, コスト `cost` の辺を追加します．何番目に追加された辺かを返します．

**制約**

- $0 \leq \mathrm{from}, \mathrm{to} \lt n$
- $0 \leq \mathrm{cap}$

**計算量**

- $O(1)$

## flow

```cpp
(1) pair<Cap, Cost> graph.flow(int s, int t)
(2) pair<Cap, Cost> graph.flow(int s, int t, Cap flow_limit)
```

$s$ から $t$ へ流せるだけ流し，その流量とコストを返します．`.first` に流量，`.second` にコストが入ります．

- (1) $s$ から $t$ へ流せるだけ流します．
- (2) $s$ から $t$ へ流量 `flow_limit` までの範囲で流せるだけ流します．

**制約**

- `slope` と同じ

**計算量**

- `slope` と同じ

## slope

```cpp
vector<pair<Cap, Cost>> graph.slope(int s, int t)
vector<pair<Cap, Cost>> graph.slope(int s, int t, Cap flow_limit)
```

返り値に流量とコストの関係の折れ線が入ります．`.first` に流量，`.second` にコストが入ります．流量 $x$ の時の最小コストを $g(x)$ とすると，全ての $x$ について $(x, g(x))$ は返り値を折れ線として見たものに含まれます．`slope`や`flow`を合わせて複数回呼んだときの挙動は未定義です．

- 返り値の最初の要素は $(0, 0)$
- 返り値の `.first` (流量) は狭義単調増加
- 3点が同一線上にあることはない
- (1) 返り値の最後の要素は最大流量を $x_\mathrm{max}$ として $(x_\mathrm{max}, g(x_\mathrm{max}))$
- (2) 返り値の最後の要素は `flow_limit` までの範囲での最大流量を $x_\mathrm{max}$ として $(x_\mathrm{max}, g(x_\mathrm{max}))$

**制約**

- グラフに負閉路が存在しない (**重要**)
- $0 \leq s, t < n$
- $s \neq t$
- `s`から`t`へ流したフローの流量が `Cap` に収まる
- 流したフローのコストの総和が `Cost` に収まる

$d_\mathrm{max}$ を辺のコストの最大値として
- (Cost : `int`): $|nd_\mathrm{max}| \leq 2 \times 10^9 + 1000$
- (Cost : `int64_t`): $|nd_\mathrm{max}| \leq 8 \times 10^{18} + 1000$

**計算量**

$F$ を流量，$m$ を追加した辺数として

- $O(F (n + m) \log (n + m))$ (負辺がないとき)
- $O(F (n + m) \log (n + m) + nm)$ (負辺があるとき)

## get_edge

```cpp
struct edge<Cap, Cost> {
    int from, to;
    Cap cap, flow;
    Cost cost;
};

(1) mcf_graph<Cap, Cost>::edge graph.get_edge(int i)
(2) vector<mcf_graph<Cap, Cost>::edge> graph.edges()
```

今の内部の辺の状態を返します．辺の順番は `add_edge` で追加された順番と同一です．

- (1): `i+1` 番目に追加した辺を返します．
- (2): 追加された辺がすべて入った配列を返します．

$m$ を追加された辺数として

**制約**

- (1): $0 \leq i \lt m$

**計算量**

- (1): $O(1)$
- (2): $O(m)$

## private変数，private関数

```cpp
int _n
struct _edge {
  int to
  int rev
  Cap cap
  Cost cost
}
vector<pair<int, int>> pos
vector<vector<_edge>> g
bool negative
```

- `_n` : グラフの頂点数
- `_edge` : グラフの辺
  - `to` : 辺の終点
  - `rev` : 逆辺の `g[to]` におけるインデックス
  - `cap` : 容量
  - `cost` : コスト
- `pos` : `pos[i]` は `i+1` 番目に追加された辺の {始点 `from`，`g[from]` におけるインデックス}
- `g` : `g[i]` は始点 `i` の辺の配列
- `negative` : 負辺があるかどうか

## ポテンシャルについて

最小費用流問題を解くとき，残余グラフには負辺が現れます．よってダイクストラ法ではなくベルマンフォード法を用いることになりますが，計算量が悪くなってしまいます．

そこで，各頂点についてポテンシャルというものを考えることにします．頂点 $v$ のポテンシャルを $p(v)$ とします．最短路を求める際の辺 $e = (u, v)$ のコストとして $\mathrm{cost}(e)$ の代わりに
$$
\mathrm{cost'}(e) = \mathrm{cost}(e) - p(v) + p(u)
$$
 を考えると，

- 容量が $0$ でないすべての辺 $e$ について $\mathrm{cost'}(e) \ge 0$ $\tag{$\diamondsuit$}$

という条件が成り立ち，ダイクストラ法を使えるようになります．以下，$s$ を始点，$t$ を終点とします．

ポテンシャルの更新方法を説明します．今，$(\diamondsuit)$ が成り立っていると仮定して $s$ から $t$ までの最短路 $P'$ を 求めます．次に，最短路上のすべての頂点 $v$ に対し，$s$ から $v$ までの距離を $\mathrm{dist'}(v)$ として $h(v) \leftarrow h(v) + \mathrm{dist'}(v) - \mathrm{dist'}(t)$ とします．この操作により $p(v)$ が $p_1(v)$ から $p_2(v)$ に，$\mathrm{cost'}(e)$ が $\mathrm{cost'_1}(e)$ から $\mathrm{cost'_2}(e)$ に変化したとき，残余グラフについても $(\diamondsuit)$ が成り立つことを確かめましょう．$P'$ 上の辺 $e = (u, v)$ について
$$
\begin{align}
\mathrm{cost'_2}(e) &= \mathrm{cost}(e) - p_2(v) + p_2(u) \\
&= \mathrm{cost}(e) - (p_1(v) + \mathrm{dist'}(v) - \mathrm{dist'}(t)) 
+ (p_1(u) + \mathrm{dist'}(u) - \mathrm{dist'}(t)) \\
&= (\mathrm{cost}(e) - p_1(v)+p_1(u)) - (\mathrm{dist'}(v) - \mathrm{dist'}(u)) \\
&= \mathrm{cost'_1}(e) - \mathrm{cost'_1}(e) \\
&= 0
\end{align}
$$
となります．また，$e$ の逆辺 $e'$ について
$$
\begin{align}
\mathrm{cost'_2}(e') &= -\mathrm{cost}(e) - p_2(u) + p_2(v) \\
&= -\mathrm{cost'_2}(e)\\
&= 0
\end{align}
$$
となります．仮定と合わせて $(\diamondsuit)$ が成り立ちます．

ポテンシャルの初期化はどうすればよいでしょうか．負辺が追加されない場合，ポテンシャルを $0$ で初期化すれば最初から $(\diamondsuit)$ が成り立ちます．負辺が追加された場合，$s$ とすべての頂点 $v$ との最短距離 $\mathrm{dist}(v)$ を求め，$p(v) = \mathrm{dist}(v) - \mathrm{dist}(t)$ とします．すると，容量が $0$ でないすべての辺 $e = (u, v)$ について
$$
\begin{align}
\mathrm{cost'}(e) &= \mathrm{cost}(e) - p(v) + p(u) \\
&= \mathrm{cost}(e) - (\mathrm{dist}(v) - \mathrm{dist}(t)) + (\mathrm{dist}(u) - \mathrm{dist}(t)) \\
&= \mathrm{cost}(e) - (\mathrm{dist}(v) - \mathrm{dist}(u)) \ge 0
\end{align}
$$
となり $(\diamondsuit)$ が成り立ちます．ただし，負閉路が存在する場合はそもそも最短距離を求められないのでこの方法が使えません．

次に，$\mathrm{cost}(e)$ を用いて求めた最短距離と $\mathrm{cost'}(e)$ を用いて求めた最短距離との関係を調べます．最短距離をそれぞれ $\mathrm{dist}(t), \mathrm{dist'}(t)$ とします．$\mathrm{cost'}(e)$ を用いて求めた最短路を $P'$ とすると
$$
\begin{align}
\mathrm{dist'}(t) &= \sum_{e \in P'} \mathrm{cost'}(e) \\
&= \sum_{e = (u, v) \in P'} \mathrm{cost}(e) - p(v) + p(u) \\
&= \sum_{e \in P'} \mathrm{cost}(e) - p(t) + p(s)
\end{align}
$$
であるので，$P'$ を求めるということは $\displaystyle \sum_{e \in P} \mathrm{cost}(e)$ が最小となるような $P$ を求めるということに他なりません．よって $\displaystyle \sum_{e \in P'} \mathrm{cost}(e) = \mathrm{dist}(t)$ です．ポテンシャルの定め方より常に $p(t) = 0$ であることと合わせて
$$
\mathrm{dist}(t) = \mathrm{dist'}(t) - p(s)
$$
 であることがわかりました．この後ポテンシャルの更新 $p(s) \leftarrow p(s) - \mathrm{dist'}(t)$ を行うと，$\mathrm{dist}(t) = -p(s)$ とよりシンプルになります．