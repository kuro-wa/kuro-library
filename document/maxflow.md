[TOC]

# Max Flow

最大流問題を解くライブラリです．

## コンストラクタ

```cpp
MaxFlow<Cap> graph(int n)
```

$n$ 頂点 $0$ 辺のグラフを作ります．`Cap` は容量の型です．

**制約**

- $0 \leq n \leq 10^8$
- `Cap` は `int / int64_t`

**計算量**

- $O(n)$

## add_vertex

```cpp
(1) V_id graph.add_vertex()
(2) vector<V_id> graph.add_vertices(int size)
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
int graph.add_edge(int from, int to, Cap cap)
```

`from` から `to` へ最大容量 `cap`，流量 $0$ の辺を追加し，何番目に追加された辺かを返します．

**制約**

$n$ を頂点数として

- $0 \leq \mathrm{from}, \mathrm{to} \lt n$
- $0 \leq \mathrm{cap}$

**計算量**

- $O(1)$

## flow

```cpp
(1) Cap graph.flow(int s, int t)
(2) Cap graph.flow(int s, int t, Cap flow_limit)
```

- (1) 頂点 `s` から `t` へ流せる限り流し，流せた量を返します．
- (2) 頂点 `s` から `t` へ流量 `flow_limit` に達するまで流せる限り流し，流せた量を返します．

この関数を呼ぶと，グラフは返り値分のフローを流した状態に変化します．

**制約**

- $s \neq t$
- 返り値が `Cap` に収まる

**計算量**

$m$ を追加された辺数として

- $O(n^2 m)$
- $O(\min(n^{\frac{2}{3}}m, m^{\frac{3}{2}}))$ (辺の容量がすべて $1$ の時)

## min_cut [未実装]

```cpp
vector<bool> graph.min_cut(int s)
```

長さ $n$ のvectorを返す．$i$ 番目の要素には，頂点 $s$ から $i$ へ残余グラフで到達可能なとき，またその時のみ `true` を返す．`flow(s, t)`をflow_limitなしでちょうど一回呼んだ後に呼ぶと，返り値は $s$, $t$ 間のmincutに対応します．詳細な挙動は [Appendix](./appendix.html) を参照してください．

**計算量**

$m$ を追加された辺数として

- $O(n + m)$

## get_edge / edges [未実装]

```cpp
struct mf_graph<Cap>::edge {
    int from, to;
    Cap cap, flow;
};

(1) mf_graph<Cap>::edge graph.get_edge(int i)
(2) vector<mf_graph<Cap>::edge> graph.edges()
```

- 今の内部の辺の状態を返す
- 辺の順番はadd_edgeで追加された順番と同一

**制約**

**計算量**

$m$ を追加された辺数として

- (1): $O(1)$
- (2): $O(m)$

## change_edge [未実装]

```cpp
void graph.change_edge(int i, Cap new_cap, Cap new_flow)
```

$i$ 番目に追加された辺の容量，流量を`new_cap`, `new_flow`に変更する．他の辺の容量，流量は変更しない．詳細は [Appendix](./appendix.html) を参照してください

**制約**

- $0 \leq \mathrm{newflow} \leq \mathrm{newcap}$

**計算量**

- $O(1)$

## private変数，private関数

```cpp
int _n
struct _edge {
  int to
  int rev
  Cap cap
}
vector<pair<int, int>> pos
vector<vector<_edge>> g
```

- `_n` : グラフの頂点数
- `_edge` : グラフの辺
  - `to` : 辺の終点
  - `rev` : 逆辺の `g[to]` におけるインデックス
  - `cap` : 容量
- `pos` : `pos[i]` は `i+1` 番目に追加された辺の {始点 `from`，`g[from]` におけるインデックス}
- `g` : `g[i]` は始点 `i` の辺の配列

## 最大流問題の計算量について

Dinic法というアルゴリズムを用いて実装しています．頂点数を $n$，辺数を $m$ として計算量は $O(n^2 m)$ です．理由は以下の通りです．

最大流問題の始点を $s$，終点 $t$ をとします．以下のステップを繰り返します．

- (1) BFSにより，容量が正の辺をコスト $1$ の辺とみなして $s$ から $t$ へのパスを探します．パスが見つからなければこれ以上フローを流せないので終了します．計算量は $O(m)$ です．内部実装では `level` に $s$ からの最短距離をメモしています．

- (2) DFSにより，$s$ から $t$ への最短路に流せる流量を求め，実際にフローを流します．内部実装では $t$ からスタートして $s$ に戻る形でパスを逆に辿っています．辺 $e$ について，
  - $e$ 以降に $s$ に辿り着くパスがない場合
  - $e$ 以降に $e$ の容量分フローを流し切り，$e$ の容量が $0$ となった場合
  
  は以後 $e$ は使わないことにします．内部実装では `iter` にどの辺まで使い終わったかをメモしています．
  
  DFSで引き返すタイミングは以下のようになります．
  
  - $s$ に辿り着いたとき，可能な限りのフローを流しつつフローが余っている頂点まで引き返します．引き返すときに辿る辺のうち容量が最小の辺の容量が $0$ となるので，使える辺は減ります． 
  - $s$ に辿り着けないとわかったときも何もせず引き返します．引き返すときに辿る辺はすべて使い終わったことになるので，使える辺は減ります．
  
  両者とも，引き返すときに動く回数は高々 $n$ 回，次に引き返し始めるまでに進む回数も高々 $n$ 回なのでDFS全体の計算量は $O(nm)$ となります．

ただし，$s$ からの最短距離，使い終わった辺はステップごとに独立に考えます．

ステップの反復回数を考えます．$s$ から $t$ への最短距離は高々 $n-1$ です．各ステップで最短路に可能な限りのフローを流しているので，$s$ から $t$ への最短距離は少なくとも $1$ ずつ増加します．よってステップ数は $O(n)$ です．以上より，Dinic法の計算量は $O(n^2 m)$ であることがわかりました．