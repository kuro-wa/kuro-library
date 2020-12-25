[TOC]

# Matrix

行列の構造体です．

以下では成分同士のすべての二項演算が定数時間で動くものと仮定したときの計算量を記述します．二項演算の計算量が $O(f(n))$ である場合はすべての計算量が $O(f(n))$ 倍となります．

## コンストラクタ

```cpp
(1) Matrix<T, zero, one> m(h, vector<T>(w))
(2) Matrix<T> m(h, vector<T>(w))
```

`vector<vector<T>>` のコンストラクタをそのまま使用できます．

- 成分の型 `T`
- `T` の加法演算子 `T + T = T`
- `T` の加法単位元を返す関数 `zero()`
- `T` の乗法演算子 `T * T = T`
- `T` の乗法単位元を返す関数 `one()`

を定義する必要があります．行列の減法を行うときには，`T` の減法演算子 `T - T = T` も定義してください．`zero`，`one` を省略した場合，加法単位元は `T(0)`，乗法単位元は `T(1)` になります．

以下，$h, w$ をコンストラクタで設定した行数と列数とします．

**制約**

- $h \times w \leq 10^8$

**計算量**

- $O(h \times w)$

## h, w

```cpp
(1) int m.h()
(2) int m.w()
```

- (1): 行数を返します．
- (2): 列数を返します．

**計算量**

- $O(1)$

## 値の取得

```cpp
(1) m[i]
(2) m[i][j]
```

`vector<vector<T>>` と同様に行えます．

- (1): `i` 行目を取得します．
- (2): `i` 行目 `j` 列目を取得します．

**制約**

- $0 \leq i < h, {\ } 0 \leq j < w$

**計算量**

- $O(1)$

## 各種演算

```cpp
+Matrix
-Matrix

Matrix += Matrix
Matrix -= Matrix
Matrix *= Matrix
Matrix *= T

Matrix + Matrix = Matrix
Matrix - Matrix = Matrix
Matrix * Matrix = Matrix
Matrix * T = Matrix
T * Matrix = Matrix
Matrix * vector<T> = vector<T>
vector<T> * Matrix = vector<t>
```
`Matrix * vector<T>` では`vector<T>` を列ベクトル，`vector<T> * Matrix` では `vector<T>` を行ベクトルをみなし，それぞれ行列の積を計算します．

`Matrix *= Matrix`，`Matrix * Matrix` では行列の積を計算することに注意してください．アマダール積 (成分ごとの積) を計算する演算子は定義されていません．

**制約**

- 行列同士の加算と減算では行数と列数が互いに等しい
- 行列同士の乗算では左辺の列数と右辺の行数が等しい

**計算量**

- $O(h^3)$ (`Matrix *= Matrix`，`Matrix * Matrix`)
- $O(h \times w)$ (それ以外)

## pow

```cpp
Matrix m.pow(int64_t n)
```

$m^n$ を返します．

**制約**

- $0 \le n$
- $h = w$

**計算量**

- $O(h^3 \log n)$

## transpose

```cpp
Matrix m.transpose()
```

`m` の転置行列を返します．

**計算量**

- $O(h \times w)$
