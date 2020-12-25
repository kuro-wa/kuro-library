[TOC]

# Segment Tree

モノイド $(S, \cdot: S \times S \to S, e \in S)$，つまり

- 結合律: 任意の $a, b, c \in S$ に対して $(a \cdot b) \cdot c$ = $a \cdot (b \cdot c)$
- 単位元の存在: 任意の $a \in S$ に対して $a \cdot e = e \cdot a = a$

を満たす代数構造に対し使用できるデータ構造です．

長さ $N$ の $S$ の配列に対し，

- 要素の $1$ 点変更
- 区間の要素の総積の取得

を $O(\log N)$ で行うことができます．

また，このライブラリはオラクルとして`op`，`e`の2種類を使用しますが，これらが定数時間で動くものと仮定したときの計算量を記述します．オラクル内部の計算量が $O(f(n))$ である場合はすべての計算量が $O(f(n))$ 倍となります．

## コンストラクタ

```cpp
(1) SegTree<S, op, e> seg(int n)
(2) SegTree<S, op, e> seg(const vector<S>& v)
```

- モノイドの型 `S`
- 二項演算 `S op(S a, S b)`
- 単位元 `S e()`

を上記の条件を満たすように定義する必要があります．具体例を[モノイド設定の例](#モノイド設定の例)に示しました．

- (1): 長さ `n` の数列 `a` を作ります．初期値は全部 `e()`です．
- (2): 長さ `n = v.size()` の数列 `a` を作ります．`v` の内容が初期値となります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## get

```cpp
S seg.get(int p)
```

`a[p]` を返します．

**制約**

- $0 \leq p < n$

**計算量**

- $O(1)$

## set

```cpp
void seg.set(int p, S x)
```

`a[p]` に `x` を代入します．

**制約**

- $0 \leq p < n$

**計算量**

- $O(\log n)$


## add

```cpp
void seg.add(int p, S x)
```

`a[p]` に `op(a[p], x)` を代入します．

**制約**

- $0 \leq p < n$

**計算量**

- $O(\log n)$

## prod

```cpp
S seg.prod(int l, int r)
```

`op(a[l], ..., a[r - 1])` を返します．$l = r$ のときは `e()` を返します．

**制約**

- $0 \leq l \leq r \leq n$

**計算量**

- $O(\log n)$

## all_prod

```cpp
S seg.all_prod()
```

`op(a[0], ..., a[n - 1])` を返します．$n = 0$ のときは `e()` を返します．

**計算量**

- $O(1)$

## max_right

```cpp
(1) int seg.max_right<f>(int l)
(2) int seg.max_right<F>(int l, F f)
```

- (1): 関数 `bool f(S x)` を定義する必要があります．segtreeの上で二分探索をします．  
- (2): `S` を引数にとり `bool` を返す関数オブジェクトを渡して使用します．  

以下の条件を両方満たす `r` を (いずれか一つ) 返します．

- `r = l` もしくは `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `r = n` もしくは `f(op(a[l], a[l + 1], ..., a[r])) = false`

`f` が単調だとすれば，`f(op(a[l], a[l + 1], ..., a[r - 1])) = true` となる最大の `r`，と解釈することが可能です．

**制約**

- `f` を同じ引数で呼んだ時，返り値は等しい (=副作用はない)
- `f(e()) = true`
- $0 \leq l \leq n$

**計算量**

- $O(\log n)$

## min_left

```cpp
(1) int seg.min_left<f>(int r)
(2) int seg.min_left<F>(int r, F f)
```

- (1): 関数 `bool f(S x)` を定義する必要があります．segtreeの上で二分探索をします．  
- (2): `S` を引数にとり `bool` を返す関数オブジェクトを渡して使用します．  

以下の条件を両方満たす `l` を(いずれか一つ)返します．

- `l = r` もしくは `f(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `l = 0` もしくは `f(op(a[l - 1], a[l], ..., a[r - 1])) = false`

`f` が単調だとすれば，`f(op(a[l], a[l + 1], ..., a[r - 1])) = true` となる最小の `l`，と解釈することが可能です．

**制約**

- `f` を同じ引数で呼んだ時，返り値は等しい (=副作用はない)
- `f(e()) = true`
- $0 \leq r \leq n$

**計算量**

- $O(\log n)$

## private変数，private関数

```cpp
int _n
int size
vector<S> d
void update(int k)
```

- `_n` : `a` の要素数．
- `size` : `_n` より大きい最小の $2$ の累乗数．
- `d` : データを管理する配列．
- `update` : `d[k]` の値を更新する関数．

## モノイド設定の例

- 区間最小値クエリ (Range Minimum Query)

  ```cpp
  using S = int;
  constexpr S IE = 1001001001;
  S op(S a, S b) { return min(a, b);}
  S e() { return IE;}
  ```

- 区間最大値クエリ (Range Max Query)

  ```cpp
  using S = int;
  constexpr S IE = -1001001001;
  S op(S a, S b) { return max(a, b);}
  S e() { return IE;}
  ```

- 区間論理積クエリ (Range AND Query)

  ```cpp
  using S = uint32_t;
  constexpr S IE = ~S(0);
  S op(S a, S b) { return a&b;}
  S e() { return IE;}
  ```

- 区間和クエリ (Range Sum Query)

  ```cpp
  using S = int;
  constexpr S IE = S(0);
  S op(S a, S b) { return a+b;}
  S e() { return IE;}
  ```

  