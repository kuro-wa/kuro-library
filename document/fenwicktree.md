[TOC]

# Fenwick Tree

長さ $N$ の配列に対し，

- 要素の $1$ 点変更
- 区間の要素の総和

を $O(\log N)$ で求めることができるデータ構造です．

## コンストラクタ

```cpp
fenwick_tree<T> fw(int n)
```

- 長さ `n` の配列 `a`を作ります．初期値はすべて $0$ です．

**制約**

- `T` は `int / uint32_t / int64_t / uint64_t / modint`
- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## add

```cpp
void fw.add(int p, T x)
```

`a[p] += x` を行います．

**制約**

- $0 \leq p < n$

**計算量**

- $O(\log n)$

## sum

```cpp
T fw.sum(int r)
T fw.sum(int l, int r)
```

`a[l] + a[l + 1] + ... + a[r - 1]` を返します．`l` を省略したときは `l = 0` となります．
`T` が整数型 (`int / uint32_t / int64_t / uint64_t`) の場合，答えがオーバーフローしたならば $\bmod 2^{\mathrm{bit}}$ で等しい値が返ります．

**制約**

- $0 \leq l \leq r \leq n$

**計算量**

- $O(\log n)$

## private変数，private関数

```cpp
int _n
vector<T> d
```

- `_n` : `a` の要素数．
- `d` : データを管理する配列．
