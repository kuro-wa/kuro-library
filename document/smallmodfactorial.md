[TOC]

# Small Mod Factorial

階乗を含む式の計算をmodを取って行う構造体です．

[Mod Factorial](modfactorial.md)とは異なり，modの値が小さく，式の中の値が大きいときに使います．

- 問題例: $0 \leq k \leq n \leq 10^{18}$ に対して，$_n C_k$ の偶奇を判定せよ．

## コンストラクタ

```cpp
SmallModFactoriall<modint> d()
```

構造体を初期化します．`modint` で答えを計算します．以下，$p$ を `modint` の法とします．

**制約**

- $p$ は素数
- $p \leq 10^8$

**計算量**

- $O(p)$

## comb

```cpp
modint d.comb(int64_t n, int64_t k)
```

$_n C_k \pmod{p}$ を返します．

**制約**

- $0 \leq n, {\ } 0 \leq k$

**計算量**

- $O(\log n)$

## private変数，private関数

```cpp
int p;
vector<modint> fact;
pair<modint, int64_t> extract(int64_t n);
```

- `p` : 法
- `fact` : `fact[i]` は $i! \pmod{p}$
- `extract` : $n = a \cdot p^e$ となる $a, e$ を返す関数


