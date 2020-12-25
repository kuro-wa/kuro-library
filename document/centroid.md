[TOC]

# Centroid Decomposition

木の重心分解を行う構造体です．

## コンストラクタ

```cpp
Centroid tree(int n)
```

$n$ 頂点の $0$ 辺のグラフを作ります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## add_edge

```cpp
void tree.add_edge(int u, int v)
```

頂点 `u` と頂点 `v` を結ぶ辺を追加します．

**制約**

- $0 \leq u, v \lt n$

**計算量**

- $O(1)$

## solve

```cpp
vector<int> solve(int v)
```

頂点 `v` を含む連結成分の重心を返します．木の重心は $1$ 個または $2$ 個であることが証明できます．

**制約**

- $0 \leq v \lt n$

**計算量**

- $O(n)$

## disable

```cpp
void disable(int v)
```

頂点 `v` を消去します．

**制約**

- $0 \leq v \lt n$

**計算量**

- $O(1)$

## enable

```cpp
void enable(int v)
```

消去された頂点 `v` を復活させます．

**制約**

- $0 \leq v \lt n$

**計算量**

- $O(1)$

## alive

```cpp
bool alive(int v)
```

頂点 `v` が消去されず残っているかを返します．

**制約**

- $0 \leq v \lt n$

**計算量**

- $O(1)$

## private変数，private関数

```cpp
int _n;
vector<int> size;
vector<char> used;
vector<vector<int>> g;
int dfs_size(int v, int p);
void dfs_centroid(int v, int p, int sz, std::vector<int> &cs);
```

- `_n` : 木の頂点数
- `size` : `size[i]` は頂点 `i` 以下の部分木のサイズ
- `used` : 頂点が消去されているかどうかの配列
- `g` : `g[i]` は頂点 `i` を始点とする辺の配列
- `dfs_size` : 頂点 `v` 以下の部分木のサイズを返す再帰関数
- `dfs_centroid` : 重心を探す再帰関数
