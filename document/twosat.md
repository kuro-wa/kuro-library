[TOC]

# 2-SAT

2-SATを解きます．
変数 $x_0, x_1, \cdots, x_{N - 1}$ に関して，

- $(x_i = f) \lor (x_j = g)$

というクローズを足し，これをすべて満たす変数の割当があるかを解きます．

## コンストラクタ

```cpp
two_sat ts(int n)
```

`n` 変数の2-SATを作ります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## add_clause

```cpp
void ts.add_clause(int i, bool f, int j, bool g)
```

$(x_i = f) \lor (x_j = g)$ というクローズを足します．

**制約**

- $0 \leq i \lt n$
- $0 \leq j \lt n$

**計算量**

- $O(1)$

## satisfiable

```cpp
bool ts.satisfiable()
```

条件を足す割当が存在するかどうかを判定する．割当が存在するならば`true`，そうでないなら`false`を返します．複数回呼ぶことも可能です．

**計算量**

足した制約の個数を $m$ として

- $O(n + m)$

## answer

```cpp
vector<bool> ts.answer()
```

最後に呼んだ `satisfiable` の，クローズを満たす割当を返します．`satisfiable` を呼ぶ前や，`satisfiable` で割当が存在しなかったときにこの関数を呼ぶと，中身が未定義の長さ `n` の `vector` を返します．

**計算量**

- $O(n)$

## private変数，private関数

```cpp
int _n;
vector<bool> _answer;
SCC scc;
```

- `_n` : 変数の数
- `_answer` : 解
- `scc` : 強連結成分分解の構造体
