[TOC]

# Kitamasa Method

数列 $\{a_n\}$ に対して，

- 最初の $m$ 項 $a_0, a_1, \ldots , a_{m-1}$

- 漸化式 $a_{n+m} = c_0 a_n + c_1 a_{n+1} + \cdots c_{m-1} a_{n+m-1}$

が与えられたとき，$n$ 項目の値 $a_n$ を$O(m^2 \log n)$ で求めることができます．

以下ではすべての二項演算が定数時間で動くものと仮定したときの計算量を記述します．二項演算の計算量が $O(f(n))$ である場合はすべての計算量が $O(f(n))$ 倍となります．

## コンストラクタ

```cpp
(1) Kitamasa<T, zero, one> d(vector<T>& v)
(2) Kitamasa<T> d(vector<T>& v)
```

- 型 `T`
- `T` の加法演算子 `T + T = T`
- `T` の加法単位元を返す関数 `zero()`
- `T` の乗法演算子 `T * T = T`
- `T` の乗法単位元を返す関数 `one()`

を定義する必要があります．

- (1): 漸化式の係数 $c_0, c_1, \ldots c_{m-1}$ をそれぞれ `v[0],  v[1], ..., v[m - 1]` で初期化します．以下，`v` のサイズを $m$ とします．
- (2): `zero`，`one` を省略した場合，加法単位元は `T(0)` ，乗法単位元は `T(1)` となります．

**制約**

- $1 \leq m \leq 10^4$

**計算量**

- $O(m)$

## solve

```cpp
T d.solve(vector<T>& a, long long n)
```

最初の $m$ 項を `a` で与えたときの $a_n$ を返します．$a_0, a_1, \ldots a_{m-1}$ をそれぞれ `a[0],  a[1], ..., a[m - 1]` とします．

**制約**

- `a` のサイズが $m$ と等しい


- $n \ge 1$

**計算量**

- $O(m^2 \log n)$

## private変数，private関数

```cpp
int m
vector<T> cs
vector<vector<T>> rs
vector<T> merge(vector<T>& xs, vector<T>& ys)
```

- `m` : 漸化式の係数の個数
- `cs` : 漸化式の係数
- `rs` : $C(2^k, 1), \ldots , C(2^k, m)$ ([Kitamasa法の計算量について](#Kitamasa法の計算量について)，[内部実装について](#内部実装について)に説明があります) をメモしておく配列
- `merge` : $C(n_1, 1), \ldots , C(n_1, m)$ と $C(n_2, 1), \ldots , C(n_2, m)$ から $C(n_1+n_2, 1), \ldots , C(n_1+n_2, m)$ を計算する関数

## Kitamasa法の計算量について

数列 $\{a_n\}$ に対して，
$$
a_n = C(n, 0) a_0 + C(n, 1) a_1 + \cdots + C(n, m-1) a_{m-1} \tag{1}
$$
となる係数 $C(n, k)$ を考えます．

- (a) $C(n, 0), \ldots , C(n, m-1)$ がわかっているとき，
  $$
  \begin{align}
  a_{n+1} &= C(n, 0) a_1 + \cdots + C(n, m-1) a_m \\
  &= C(n, m-1) a_0 + (C(n, 0) + C(n, m-1)) a_1 + \cdots +(C(n, m-2) + C(n, m-1)) a_{m-1}
  \end{align}
  $$
  と表せるので，$C(n＋1, 0), \ldots C(n+1, m-1)$ が $O(m)$ で求まります．

- (b) $C(n_1, 0), \ldots , C(n_1, m-1)$ と $C(n_2, 0), \ldots , C(n_2, m-1)$ がわかっているとき，
  $$
  a_{n_1+n_2} = C(n_1, 0) a_{n_2} + \cdots + C(n, m-1) a_{n_2+m-1}
  $$
  と表せます．(a) の方法により $a_{n_2+1}, \ldots a_{n_2+m-1}$ をそれぞれ $O(m)$ で $(1)$ 式の形に直せるので，$C(n_1+n_2, 0), \ldots , C(n_1+n_2, m-1)$ が $O(m^2)$ で求まります．
  

以上により，繰り返し $2$ 乗法を用いて $a_n$ が $O(m^2 \log n)$ で求まります．具体的には，$C(2^k, 0), \ldots , C(2^k, m-1) {\ } (0 \leq k \leq \lfloor \log_2 n \rfloor)$ を計算しながら，$n$ の $k+1$ ビット目が立っていたら (b) の方法で係数にマージするという操作を行えばよいです．

## 内部実装について

実装上，構造体内部は1-indexedです．(b) の操作を行う際には，一旦
$$
a_{n_1+n_2} = d_1 a_1 + \cdots + d_{2m} a_{2m}
$$
の形に表してから $a_{2m}, \ldots , a_{m+1}$ の順に消去しています．また，係数の初期値を $C(1, 1), \ldots , C(1, m)$ とし，ここに $C(n, 1), \ldots , C(n, m)$ をマージすることで $C(n+1, 1), \ldots , C(n+1, m)$ を求めています．よって結果は $a_{n+1}$ となりますが，これを0-indexedに直すと $a_n$ なので正しく答えが求まっていることがわかります．