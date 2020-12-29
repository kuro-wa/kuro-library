[TOC]

# Suffix Array

文字列，あるいは配列の接尾辞を扱う構造体です．接尾辞配列は，辞書順でソートされた接尾辞を開始位置のインデックスで管理します．

## コンストラクタ

```cpp
(1) SuffixArray sa(const string& s)
(2) SuffixArray<S> sa(const S& s)
```

- (1) 文字列 `s` の接尾辞配列を作ります．
- (2) 型 `S` の配列 `s` の接尾辞配列を作ります．

以下，$n$ をコンテナのサイズとします．

**制約**

- $n \leq 10^8$

**計算量**

- $O(n (\log n)^2)$

## 値の取得

```cpp
int sa[i]
```

接尾辞配列の `i` 番目の要素を取得します．

**制約**

- $0 \leq i \leq n$

**計算量**

- $O(1)$


## lower_bound

```cpp
int lower_bound(S t)
```

$k$ を `t` の長さとして，`s[sa[i]..min(k, n-1)]` が辞書順で初めて `t` 以上となるような `i` を返します．そのような `i` が存在しないとき，`n` を返します．

**制約**

- $0 \leq k$

**計算量**

- $O(k \log n)$


## upper_bound

```cpp
int upper_bound(S t)
```

$k$ を `t` の長さとして，`s[sa[i]..min(k, n-1)]` が辞書順で初めて `t` より大きくなるような `i` を返します．そのような `i` が存在しないとき，`n` を返します．

**制約**

- $0 \leq k$

**計算量**

- $O(k \log n)$


## count

```cpp
int count(S t)
```

`s` の中に `t` がいくつ含まれているかを返します．

**制約**

$k$ を `t` の長さとして

- $0 \leq k$

**計算量**

- $O(k \log n)$

## private変数，private関数

```cpp
S _s;
vector<int> sa;
```

- `_s` : 文字列，あるいは配列
- `sa` : 接尾辞配列

