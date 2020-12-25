[TOC]

# Lowest Common Ancestor

根付き木に対して最小共通祖先に関する問題を扱う構造体です．

## コンストラクタ

```cpp
(1) LCA tree(int n)
(2) LCA<Cost> tree(int n)
```

$n$ 頂点の $0$ 辺のグラフを作ります．辺にコストがある場合，型 `Cost` を指定してください．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## add_edge

```cpp
(1) void tree.add_edge(int u, int v)
(2) void tree.add_edge(int u, int v, Cost cost)
```

- (1): 頂点 `u` と頂点 `v` を結ぶ辺を追加します．
- (2): 頂点 `u` と頂点 `v` を結ぶコスト `cost` の辺を追加します．

**制約**

- $0 \leq u, v \lt n$

**計算量**

- $O(1)$

## init

```cpp
(1) void init()
(2) void init(int root=0)
```

- (1): 頂点 `0` を根として木を初期化します．
- (2): 頂点 `root` を根として木を初期化します．

辺を追加し終わったら必ず実行してください．以降の関数は `init` をしてからでなければ機能しません．

**計算量**


- $O(n \log n)$

## query

```cpp
int tree.query(int u, int v)
```

頂点 `u` と頂点 `v` の最小共通祖先を返します．

**制約**

- $0 \leq u, v \lt n$

**計算量**

- $O(\log n)$

## length

```cpp
(1) int tree.length(int u, int v)
(2) int tree.length(int u)
```

頂点 `u` と頂点 `v` の間のパスに含まれる頂点数を返します．辺のコストをすべて $1$ とみなしたときの距離に相当します．第 $2$ 引数を省略すると根からの深さを返します．

**制約**

- $0 \leq u, v \lt n$

**計算量**

- $O(\log n)$

## dist

```cpp
(1) Cost tree.dist(int u, int v)
(2) Cost tree.dist(int u)
```

頂点 `u` と頂点 `v` の間のパスの距離を返します．第 $2$ 引数を省略すると根からの距離を返します．

**制約**

- $0 \leq u, v \lt n$

**計算量**

- $O(\log n)$

## up

```cpp
int tree.up(int v, int l)
```

頂点 `v` から根に向かって辺を `l` 個登ったときの頂点を返します．根を越えてしまう場合，`-1` を返します．

**制約**

- $0 \leq u < n$

**計算量**

- $O(\log n)$

## private変数，private関数

```cpp
int _n;
int _root;
int log;
struct edge {
  int to;
  Cost cost;
};
vector<vector<edge>> g;
vector<vector<int>> par;
vector<int> depths;
vector<Cost> dists;
void dfs(int v, int p, int d, Cost c);
```

- `_n` : 木の頂点数
- `_root` : 根
- `log` : $\lceil \log_2 \_n \rceil$
- `edge` : 辺
  - `to` : 終点
  - `cost` : コスト
- `g` : `g[i]` は頂点 `i` を始点とする辺の配列
- `par` : `par[i]` は根に向かって $2^i$ 個だけ上の頂点 (なければ `_n`)
- `depths` : 根からの深さの配列
- `dists` : 根からの距離の配列
- `dfs` : 頂点 `v` から 親 `p` ，根からの深さ `d`，根からの距離 `c` として深さ優先探索をする関数
