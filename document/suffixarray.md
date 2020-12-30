[TOC]

# Suffix Array

文字列，あるいは配列の接尾辞を扱う構造体です．Suffix Arrayは，辞書順でソートされた接尾辞を開始位置のインデックスで管理します．列 `s` の $a$ 番目から $b - 1$ 番目の要素のsubstringを，`s[a..b)` と表記します．ただし，`s[a..a)` は空文字列とします．

## コンストラクタ

```cpp
(1) SuffixArray sa(const string& s)
(2) SuffixArray sa(const vector<T>& s)
```

- (1) 文字列 `s` のSuffix Arrayを作ります．
- (2) 型 `T` の配列 `s` のSuffix Arrayを作ります．

以下，$n$ を列 `s` の長さとします．Suffix Array `sa` は $(0, 1, \dots, n)$ の順列であって，各 $i = 0, 1, \cdots , n-1$ について `s[sa[i]..n) < s[sa[i+1]..n)` を満たします．

**制約**

- $n \leq 10^8$

**計算量**

- $O(n (\log n)^2)$

## 値の取得

```cpp
int sa[i]
```

Suffix Arrayの `i` 番目の要素を取得します．`sa[0] = n` が常に成り立ちます．

**制約**

- $0 \leq i \leq n$

**計算量**

- $O(1)$


## lower_bound

```cpp
(1) int lower_bound(string t)
(2) int lower_bound(vector<T> t)
```

$k$ を `t` の長さとして，`s[sa[i]..min(i+k, n)]` が辞書順で初めて `t` 以上となるような `i` を返します．そのような `i` が存在しないとき，`n` を返します．

**制約**

- $0 \leq k$

**計算量**

- $O(k \log n)$


## upper_bound

```cpp
(1) int upper_bound(string t)
(2) int upper_bound(vector<T> t)
```

$k$ を `t` の長さとして，`s[sa[i]..min(i+k, n)]` が辞書順で初めて `t` より大きくなるような `i` を返します．そのような `i` が存在しないとき，`n` を返します．

**制約**

- $0 \leq k$

**計算量**

- $O(k \log n)$


## count

```cpp
(1) int count(string t)
(2) int count(vector<T> t)
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
- `sa` : Suffix Array

