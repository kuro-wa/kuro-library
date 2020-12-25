[TOC]

# Range Sum Query

長さ $N$ の配列に対し，

- 区間の要素に一括で $x$ を加算
- 区間の要素の総和の取得

を $O(\log N)$ で行うことができるデータ構造です．

また，以下ではすべての二項演算が定数時間で動くものと仮定したときの計算量を記述します．二項演算の計算量が $O(f(n))$ である場合はすべての計算量が $O(f(n))$ 倍となります．

## コンストラクタ

```cpp
(1) RSQ<T, F> d(int n)
(2) RSQ<T, F> d(vector<T> v)
(3) RSQ<T> d(int n)
(4) RSQ<T> d(vector<T> v)
```

- 要素の型 `T`
- `T` の単位元 `T(0)`
- 作用素の型 `F` (省略すると `F = T`)
- `F` の単位元 `F(0)`
- 演算子 `T + T = T`，`F + T = T`，`F + F = F`，`F * int = F`

を定義する必要があります．`T, F` が `int / int64_t / double` などの基本データ型の場合は定義し直す必要はありません．


- (1): 長さ `n` の数列 `a` を作ります．初期値は全部 `T(0)` です．
- (2): 長さ `n = v.size()` の数列 `a` を作ります．`v` の内容が初期値となります．
- (3), (4): `F` を省略した場合，`F = T` となります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## set

```cpp
void d.set(int p, T x)
```

`a[p]` に `x` を代入します．

**制約**

- $0 \leq p < n$

**計算量**

- $O(\log n)$

## get

```cpp
T d.get(int p)
```

`a[p]` を返します．

**制約**

- $0 \leq p < n$

**計算量**

- $O(\log n)$

## prod

```cpp
T d.prod(int l, int r)
```

`a[l] + ... + a[r - 1]` を返します．$l = r$ のときは `T(0)` を返します．

**制約**

- $0 \leq l \leq r \leq n$

**計算量**

- $O(\log n)$

## all_prod

```cpp
T d.all_prod()
```

`a[0] + ... + a[n-1]` を返します．$n = 0$ のときは `T(0)` を返します．

**計算量**

- $O(1)$

## apply

```cpp
(1) void d.apply(int p, F f)
(2) void d.apply(int l, int r, F f)
```

- (1) `a[p] = f + a[p]` とします．
- (2) `i = l, ..., r-1` に対して `a[i] = f + a[i]` とします．

**制約**

- (1) $0 \leq p < n$
- (2) $0 \leq l \leq r \leq n$

**計算量**

- $O(\log n)$

## private変数，private関数

```cpp
struct S {
  T x
  int l
  S(T x, int l)
}
static S op(S a, S b)
static S e()
static S mapping(F f, S s)
static F composition(F f, F g)
static F id()
LazySegTree<S, op, e, F, mapping, composition, id> d
```

- `S` : 区間の総和を管理する構造体
  - `x` : 区間の総和
  - `l` : 区間の長さ
  - コンストラクタ
- `op` : `S` の二項演算
- `e` : `S` の単位元を返す関数
- `mapping` : `F` の要素を`S` の要素に作用させる関数
- `composition` : `F` の二項演算
- `id` : `F` の単位元を返す関数
- `d` : `S` を管理するlazy segtree
