[TOC]

# Math

数論的アルゴリズム詰め合わせです．

## extgcd

```cpp
T extgcd(T a, T b, T& x, T& y)
```

拡張ユークリッドの互除法を行います．$ax+by = \gcd(a, b)$ を満たす $(x, y)$ の組を見つけて引数に上書きし，$\gcd(a, b)$ を返します．$\gcd(a, b)$ は正の値になります．

**制約**

- `T` は `int / int64_t`
- $(a, b) \neq (0, 0)$

**計算量**

- $O(\log \min(a, b))$

## divisor

```cpp
vector<int64_t> divisor(int64_t n)
```

`n` のすべての約数を昇順で返します．

**制約**

- $0 \leq n$

**計算量**

- $O(\sqrt{n})$

## pow_mod

```cpp
int64_t pow_mod(int64_t x, int64_t n, int64_t m)
```

$x^n \bmod m$ を返します．

**制約**

- $0 \le n$
- $1 \le m$

**計算量**

- $O(\log n)$


## moebius

```cpp
map<int64_t, int> moebius(int64_t n)
```

`n` の約数についてメビウス関数 $\mu$ を構築します．キーに `n` の約数 $d$，値に $\mu(d)$ が入ります．

メビウスの反転公式「$\displaystyle g(n) = \sum_{d|n} f(d)$ のとき $\displaystyle f(n) = \sum_{d|n} \mu(d) g(\frac{n}{d})$」の証明は[こちら](https://mathtrain.jp/mobiusinversion)．

**制約**

- $0 \le n$

**計算量**

- $O(\sqrt{n})$

## crt

```cpp
pair<int64_t, int64_t> crt(vector<int64_t> r, vector<int64_t> m)
```

同じ長さの配列 $r, m$ を渡します．この配列の長さを $n$ としたとき，
$$
x \equiv r[i] \pmod{m[i]}, \forall i \in \lbrace 0,1,\cdots, n - 1 \rbrace
$$
を解きます。答えは(存在するならば) $y, z (0 \leq y < z = \mathrm{lcm}(m[i]))$ を用いて $x \equiv y \pmod z$ の形で書けることが知られており、この $(y, z)$ をpairとして返します．答えがない場合は $(0, 0)$ を返します．$n=0$ のときは $(0, 1)$ を返します．

**制約**

- $|r| = |m|$
- $1 \le m[i]$
- $\mathrm{lcm}(m[i])$ が `int64_t` に収まる

**計算量**

- $O(n \log{\mathrm{lcm}(m[i])})$
