[TOC]

# Mod int

自動でmodを取る構造体です．

法が固定ならば `modint998244353` あるいは `modint1000000007`，法が入力で与えられるならば `modint` を使えばほとんどの問題に対応できます．以下の関数らは，`set_mod` を除き $3$ つともに対して動きます．

## コンストラクタ

```cpp
(1) modint x()
(2) modint x(int64_t v)
```

- (1) modintのデフォルトコンストラクタです．$0$ が格納されます．
- (2) 整数型に対するコンストラクタです．`v` のmodを取ってmodintに格納します．

## set_mod

```cpp
void modint::set_mod(int m)
```

modを設定します．入力で法が与えられる場合に使います．最初に呼んでください．

**制約**

- $1 \leq m \leq 2 \times 10^9 + 1000$

**計算量**

- $O(1)$

## mod

```cpp
int modint::mod()
```

modを返します．

## val

```cpp
int x.val();
```

`x`に格納されている値を返します．

## 各種演算

```cpp
-modint;

modint++;
modint--;
++modint;
--modint;

modint + modint;
modint - modint;
modint * modint;
modint / modint;

modint += modint;
modint -= modint;
modint *= modint;
modint /= modint;

modint == modint;
modint != modint;
modint < modint

ostream << modint
istream >> modint

(T)modint
```

が動きます．

```cpp
modint x = 10;
1 + x;
```

も (`modint(1) + x`と自動で解釈されるので) 動きます．

```cpp
modint::set_mod(11);
modint y = 10;
int z = 1234;
y * z;
```

も `y * modint(z)` と解釈され，動きます．

また，明示的なキャストのみが可能です．

**制約**

- `a / b`(or `a /= b`)を行なう時，`gcd(b.val(), mod) == 1`

**計算量**

- $O(1)$ (割り算以外)
- $O(\log \mathrm{mod})$ (割り算)

## pow

```cpp
modint x.pow(int64_t n)
```

$x^n$ を返します．

**制約**

- $0 \le n$

**計算量**

- $O(\log n)$

## inv

```cpp
modint x.inv()
```

逆元，つまり $xy \equiv 1$ なる $y$ を返します．

**制約**

- `gcd(x.val(), mod) = 1`

**計算量**

- $O(\log \mathrm{mod})$

## raw

```cpp
modint modint::raw(int x)
```

`x` に対してmodを取らずに，`modint(x)` を返します．

定数倍高速化のための関数です．

上で述べたように

```cpp
modint a;
int i;
a += i;
```

は，`i`がmod以上でも動きます．勝手に`i`に対してmodを取るためです．

ですが，例えば以下のようなコードでは，`i`がmodを超えないことを保証できます．

```cpp
int main() {
    modint::set_mod(1000000007);
    modint a = 1;
    for (int i = 1; i < 100000; i++) {
        a += i;
    }
}
```

このようなときに，

```cpp
int main() {
    modint::set_mod(1000000007);
    modint a = 1;
    for (int i = 1; i < 100000; i++) {
        a += modint::raw(i);
    }
}
```

と書くと，modの回数を減らすことが出来ます．

当然ながら `modint::raw(x)` にmod以上の値を入れたときの挙動は未定義です．

**制約**

- $0 \leq x \lt \mathrm{mod}$

## private変数，private関数

```cpp
uint32_t _v
static uint32_t _m
static uint32_t normalize(int64_t v)
```

- `_n` : 余りを取った値
- `_m` : 法
- `normalize` : 余りを取る関数

## Tips (other mod)

問題文で他のmod (例: `1000000009`) が与えられる場合，以下のように書けます

```cpp
using mint = StaticModint<1000000009>;
```

`modint998244353`，`modint1000000007` は，`StaticModint<998244353>`，`StaticModint<1000000007>`のエイリアスになっています．

```cpp
using modint998244353 = StaticModint<998244353>;
using modint1000000007 = StaticModint<1000000007>;
```

## Tips (複数mod)

複数種類modを使用したい場合以下のようにできます

```cpp
using mint0 = DynamicModint<0>;
using mint1 = DynamicModint<1>;
```

`modint`は，`DynamicModint<-1>`のエイリアスになっています．

```cpp
using modint = DynamicModint<-1>;
```


