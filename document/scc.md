[TOC]

# Strongly Connected Components

有向グラフを強連結成分分解します．

## コンストラクタ

```cpp
scc_graph graph(int n)
```

$n$ 頂点 $0$ 辺の有向グラフを作ります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## add_edge

```cpp
void graph.add_edge(int from, int to)
```

頂点 `from` から頂点 `to` へ有向辺を追加します．

**制約**

- $0 \leq \mathrm{from} \lt n$
- $0 \leq \mathrm{to} \lt n$

**計算量**

- $O(1)$

## solve

```cpp
vector<vector<int>> graph.solve()
```

以下の条件を満たすような，「頂点のリスト」のリストを返します．

- 全ての頂点がちょうど1つずつ，どれかのリストに含まれます．
- 内側のリストと強連結成分が一対一に対応します．リスト内での頂点の順序は未定義です．
- リストはトポロジカルソートされています．異なる強連結成分の頂点 $u, v$ について，$u$ から $v$ に到達できる時，$u$ の属するリストは $v$ の属するリストよりも前です．

**計算量**

追加した辺の本数を $m$ として

- $O(n + m)$

## order

```cpp
vector<int> graph.order()
```

各頂点が何番目の強連結成分に属するかを返します．`solve` の後に呼んでください．

**計算量**

- $O(n)$

## private変数，private関数

```cpp
int _n;
struct edge { int to;};
vector<pair<int, edge>> edges;
vector<vector<int>> groups;
vector<int> ids;
template<typename E> struct csr {
  vector<int> start;
  vector<E> elist;
};
int scc_ids();
```

- `_n` : グラフの頂点数
- `edge` : グラフの辺
  - `to` : 辺の終点
- `edges` : 追加された辺の配列
- `ids` : 頂点が所属する強連結成分の番号の配列
- `groups` : トポロジカルソートされた強連結成分の配列
- `csr` : 追加された辺を一次元の隣接リストとして持つ構造体 (高速化用)
  - `start` : `elist[start[i]]` から `elist[start[i+1]]-1` までが始点 `i` の辺
  - `elist` : 始点順にソートされた辺の配列
- `scc_ids` : 各頂点が何番目の強連結成分に属するかを `ids` に書き込み，強連結成分の個数を返す関数．
