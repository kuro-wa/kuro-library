[TOC]

# Sieve of Eratosthenes

エラトステネスの篩を用いて，

- 素数判定

- 素因数分解
  

を高速に行います．[AtCoder Live Libraryのもの](https://github.com/atcoder/live_library/blob/master/prime.cpp)とほとんど同じです．

## コンストラクタ

```cpp
Sieve d(int n)
```

`n` を上限としてエラトステネスの篩を構築します．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n \log \log n)$

## primes

```cpp
vector<int> d.primes()
```

`n` 以下の素数を昇順で返します．

**制約**

**計算量**

- $O(n)$

## is_prime

```cpp
bool d.is_prime(T x)
```

`x` が素数かどうかを返します．

**制約**

- `T` は `int / int64_t`
- `T` が `int` のとき $0 \leq x \leq n$
- `T` が `int64_t` のとき $0 \leq x \leq n^2$

**計算量**

- `T` が `int` のとき $O(1)$
- `T` が `int64_t` のとき $O(\sqrt{n} / \log n)$

## factor

```cpp
map<T, int> d.factor(T x)
```

`x` の素因数分解を返します．キーに素因数，値に指数が入ります．

**制約**

- `T` は `int / int64_t`
- `T` が `int` のとき $0 \leq x \leq n$
- `T` が `int64_t` のとき $0 \leq x \leq n^2$

**計算量**

- `T` が `int` のとき $O(\log n)$
- `T` が `int64_t` のとき $O(\sqrt{n})$

## private変数，private関数

```cpp
int n
vector<int> f
vector<int> ps
vector<int> factor_list(int x)
```

- `n` : エラトステネスの篩の上限
- `f` : `f[i]` は `i` の最小の素因数
- `ps` : `ps[i]` は `n` 以下の `i+1` 番目の素数
- `factor_list` : `x` のすべての素因数を重複を含めて昇順で返す関数
