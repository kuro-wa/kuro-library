[TOC]

# Segment Sieve of Eratosthenes

エラトステネスの篩を用いて，

- 素数判定

- 素因数分解
  

を高速に行います．Sieve of Eratosthenes と異なり，指定された区間内の整数を扱います．

## コンストラクタ

```cpp
SegSieve d(int64_t a, int64_t b)
```

区間 $[a, b)$ でエラトステネスの篩を構築します．

**制約**

- $0 \leq a < b$
- $b-a \leq 10^8$

**計算量**

- $O(\sqrt{b} \log \log b + (b-a))$

## primes

```cpp
vector<int64_t> d.primes()
```

区間 $[a, b)$ の素数を昇順で返します．

**制約**

**計算量**

- $O(b-a)$

## is_prime

```cpp
bool d.is_prime(int64_t x)
```

`x` が素数かどうかを返します．

**制約**

- $a \leq x < b$

**計算量**

-  $O(1)$

## private変数，private関数

```cpp
int64_t a
int64_t b
vector<int> f
vector<int64_t> f2
vector<int> ps
```

- `a` : エラトステネスの篩の左端．
- `b` : エラトステネスの篩の右端 (この点は含まない)．
- `f` : `f[i]` は `i` の最小の素因数．
- `f2` : `f2[i-a]` は `i` の最小の素因数．
- `ps` : `ps[i]` は $[a, b)$ の `i+1` 番目の素数．

