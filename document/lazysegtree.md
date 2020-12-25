[TOC]

# Lazy Segment Tree

モノイド $(S, \cdot: S \times S \to S, e \in S), {\ }(F, \circ: F \times F \to F, \mathrm{id} \in F)$ に対して，$F$ が $S$ から $S$ への写像の集合であって，以下の条件を満たすときに使用できるデータ構造です．

- $F$ の単位元 $\mathrm{id}$ は恒等写像である．つまり，任意の $x \in S$ に対し $\mathrm{id}(x) = x$ を満たす．
- $F$ は写像の合成について閉じている．つまり，任意の $f, g \in F$ に対し $f \circ g \in F$ である．
- 任意の $f \in F, x, y \in S$ に対し $f(x \cdot y) = f(x) \cdot f(y)$ をみたす．

長さ $N$ の $S$ の配列に対し，

- 区間の要素に一括で $F$ の要素 $f$ を作用 ($x \leftarrow f(x)$ )
- 区間の要素の総積の取得

を $O(\log N)$ で行うことができます．

また，このライブラリはオラクルとして`op, e, mapping, composition, id`を使用しますが，これらが定数時間で動くものと仮定したときの計算量を記述します．オラクル内部の計算量が $O(f(n))$ である場合はすべての計算量が $O(f(n))$ 倍となります．

## コンストラクタ

```cpp
(1) LazySegTree<S, op, e, F, mapping, composition, id> seg(int n)
(2) LazySegTree<S, op, e, F, mapping, composition, id> seg(vector<T>& v)
```

- モノイドの型 `S`
- $S$ の二項演算 `S op(S a, S b)`
- $S$ の単位元 `S e()`
- 写像の型 `F`
- $f \in F, x \in S$ に対して $f(x) \in S$ を返す関数 `S mapping(F f, S x)`
- $F$ の二項演算，つまり写像の合成 `F composition(F f, F g)`
- $F$ の単位元，つまり恒等写像 `F id()`

を上記の条件を満たすように定義する必要があります．

- (1): 長さ `n` の数列 `a` を作ります．初期値は全部 `e()` です．
- (2): 長さ `n = v.size()` の数列 `a` を作ります．`v` の内容が初期値となります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## set

```cpp
void seg.set(int p, S x)
```

`a[p]` に `x` を代入します．

**制約**

- $0 \leq p < n$

**計算量**

- $O(\log n)$

## get

```cpp
S seg.get(int p)
```

`a[p]` を返します．

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

`op(a[0], ..., a[n-1])` を返します．$n = 0$ のときは `e()` を返します．

**計算量**

- $O(1)$

## apply

```cpp
(1) void seg.apply(int p, F f)
(2) void seg.apply(int l, int r, F f)
```

- (1) `a[p] = f(a[p])` とします．
- (2) `i = l, ..., r-1` に対して `a[i] = f(a[i])` とします．

**制約**

- (1) $0 \leq p < n$
- (2) $0 \leq l \leq r \leq n$

**計算量**

- $O(\log n)$

## max_right [未実装]

```cpp
(1) int seg.max_right<g>(int l)
(2) int seg.max_right<G>(int l, G g)
```

- (1): 関数 `bool g(S x)` を定義する必要があります．segtreeの上で二分探索をします．  
- (2): `S` を引数にとり `bool` を返す関数オブジェクトを渡して使用します．  

以下の条件を両方満たす `r` を(いずれか一つ)返します．

- `r = l` もしくは `g(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `r = n` もしくは `g(op(a[l], a[l + 1], ..., a[r])) = false`

`g` が単調だとすれば，`g(op(a[l], a[l + 1], ..., a[r - 1])) = true` となる最大の `r`，と解釈することが可能です．

**制約**

- `g` を同じ引数で呼んだ時，返り値は等しい (=副作用はない)
- `g(e()) = true`
- $0 \leq l \leq n$

**計算量**

- $O(\log n)$

## min_left [未実装]

```cpp
(1) int seg.min_left<g>(int r)
(2) int seg.min_left<G>(int r, G g)
```

- (1): 関数 `bool g(S x)` を定義する必要があります．segtreeの上で二分探索をします．  
- (2): `S`を引数にとり`bool`を返す関数オブジェクトを渡して使用します．  

以下の条件を両方満たす `l` を(いずれか一つ)返します．

- `l = r` もしくは `g(op(a[l], a[l + 1], ..., a[r - 1])) = true`
- `l = 0` もしくは `g(op(a[l - 1], a[l], ..., a[r - 1])) = false`

`g` が単調だとすれば，`g(op(a[l], a[l + 1], ..., a[r - 1])) = true` となる最小の `l`，と解釈することが可能です．

**制約**

- `g` を同じ引数で呼んだ時，返り値は等しい (=副作用はない)
- `g(e()) = true`
- $0 \leq r \leq n$

**計算量**

- $O(\log n)$

## private変数，private関数

```cpp
int _n
int	size
int log
vector<S> d
vector<F> lz
void update(int k)
void all_apply(int k, F f)
void push(int k)
```

- `_n` : `a` の要素数
- `size` : `_n` より大きい最小の $2$ の累乗数
- `log` : $\log_2 \mathrm{size}$
- `d` : データを管理する配列
- `lz` : データに作用させる要素を一時的に溜めておく配列
- `update` : `d[k]` の値を更新する関数
- `all_apply` : `d[k]` 以降のデータに `f` を作用させる関数
- `push` : `lz[k]` に溜めておいた要素をデータにに作用させる関数

## モノイド設定の例

- 区間加算・区間最小値クエリ (Range Add Query & Range Minimum Query)

  ```cpp
  using S = int;
  using F = int;
  const S IE = 1001001001;
  S op(S a, S b) { return min(a, b);}
  S e() { return IE;}
  S mapping(F f, S s) { return f+s;}
  F composition(F f, F g) { return f+g;}
  F id() { return F(0);}
  ```

