[TOC]

# Fraction

分数を扱う構造体です．

## コンストラクタ

```cpp
(1) Fraction<T> x()
(2) Fraction<T> x(T a)
(3) Fraction<T> x(T a, T b)
```

- (1) Fractionのデフォルトコンストラクタです．$0$ が格納されます．
- (2) Fractionに整数 `a` を格納します．
- (3) Fractionに分数 `a / b` を格納します．約分が自動で行われます．

**制約**

- `T` は `int / int64_t`
- (3): $b \neq 0$

**計算量**

- $O(\log (\min (a, b)))$

## numerator, denominator

```cpp
(1) T x.numerator()
(2) T x.denominator()
```

- (1) 分子を返します．
- (2) 分母を返します．必ず正の整数です．

**計算量**

- $O(1)$

## 各種演算

```cpp
+Fraction
-Fraction

Fraction + Fraction
Fraction - Fraction
Fraction * Fraction
Fraction / Fraction

Fraction += Fraction
Fraction -= Fraction
Fraction *= Fraction
Fraction /= Fraction

Fraction == Fraction
Fraction != Fraction
Fraction < Fraction
Fraction > Fraction
Fraction <= Fraction
Fraction >= Fraction

ostream << Fraction

(T)Fraction
```

が動きます．

```cpp
Fraction x(1, 2);
1 + x;
```

も (`Fraction(1) + x` と自動で解釈されるので) 動きます．

```cpp
Fraction y(2, 3);
int z = 1234;
y * z;
```

も `y * Fraction(z)` と解釈され，動きます．

小数型は整数に丸められてからコンストラクタ引数に渡されるため，正確な演算はできないことに注意してください．

出力形式は `a/b` です．

また，明示的なキャストのみが可能です．

```cpp
Fraction u(3, 2);
int v = (int)u;
double w = (double)u;
```

とすると，`v = 1`，`w = 1.5` となります．

**制約**

- `a / b`(or `a /= b`)を行なう時，`gcd(b.val(), mod) == 1`

**計算量**

- $O(1)$ (単項演算子，比較演算子，出力)
- $O(\log (\min(a, b)))$ (それ以外)

## floor

```cpp
T x.floor()
```

$\left\lfloor \dfrac{a}{b} \right\rfloor$ を返します．

**計算量**

- $O(1)$

## ceil

```cpp
T x.ceil()
```

$\left\lceil \dfrac{a}{b} \right\rceil$ を返します．

**計算量**

- $O(1)$

## private変数

```cpp
T num;
T den;
```

- `num` : 分子
- `den` : 分母