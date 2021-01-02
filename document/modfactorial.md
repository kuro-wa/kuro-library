[TOC]

# Mod Factorial

階乗を含む式の計算をmodを取って行う構造体です．

[Small Mod Factorial](smallmodfactorial.md)とは異なり，式の中の値が小さいときに使います．

- 問題例: $0 \leq k \leq n \leq 10^6$ に対して，$_n C_k$ を $998244353$ で割った余りを求めよ．

## コンストラクタ

```cpp
ModFactoriall<modint> d(int ub)
```

構造体を初期化します．`modint` で答えを計算します．式の中の値の上限 `ub` を指定してください．指定しない場合 $2 \times 10^6 + 5$ が上限になります． 以下，$m$ を `modint` の法とします．

**制約**

- $\mathrm{ub} \leq 10^8$

**計算量**

- $O(\mathrm{ub} + \log m)$

## fact

```cpp
modint d.fact(int n)
```

$n! \pmod{m}$ を返します．

**制約**

- $0 \leq n \leq \mathrm{ub}$

**計算量**

- $O(1)$

## ifact

```cpp
modint d.fact(int n)
```

$(n!)^{-1} \pmod{m}$ を返します．

**制約**

- $0 \leq n \leq \mathrm{ub}$

**計算量**

- $O(1)$

## comb

```cpp
modint d.comb(int n, int k)
```

$_n C_k \pmod{m}$ を返します．

**制約**

- $0 \leq n \leq \mathrm{ub}, {\ } 0 \leq k$

**計算量**

- $O(1)$

## perm

```cpp
modint d.perm(int n, int k)
```

$_n P_k \pmod{m}$ を返します．

**制約**

- $0 \leq n \leq \mathrm{ub}, {\ } 0 \leq k$

**計算量**

- $O(1)$

## homo

```cpp
modint d.homo(int n, int k)
```

重複組み合わせ $_n H_k \pmod{m}$ を返します．

- $n$ 種類から $k$ 個のものを選ぶ場合の数
- $n$ 個の箱に区別できない $k$ 個のボールを入れる場合の数
- $(x_1 + x_2 + \cdots +x_n)^k$ を展開したときの項の種類数
- $_{n+k-1} C_k = _{n+k-1} C_{n-1}$

に等しくなります．

**制約**

- $0 \leq n+r-1 \leq \mathrm{ub}, {\ } 0 \leq k$

**計算量**

- $O(1)$

## multiperm

```cpp
modint d.multiperm(vector<int> a)
```

$n$ を `a` の長さとして，同じものを含む順列 (permutations with multisets)
$$
\frac{\left(\displaystyle\sum_{i = 0}^{n-1} a_i\right)!}{a_0! a_1! \cdots a_{n-1}!}
$$
を返します．

**制約**

- すべての $i$ に対して $0 \leq a_i$
- $\displaystyle\sum_{i = 0}^{n-1} a_i \leq \mathrm{ub}$

**計算量**

- $O(1)$

## private変数，private関数

```cpp
int ub;
vector<modint> facts
vector<modint> ifacts;
```

- `ub` : 上限
- `facts` : `facts[i]` は $i! \pmod{p}$
- `ifacts` : `ifacts[i]` は $(i!)^{-1} \pmod{p}$


