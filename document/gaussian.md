[TOC]

# Gaussian Elimination

ガウスの消去法により

- 連立一次方程式の解
- 行列のランク
- 行列式
- 逆行列

を計算します．行列として[Matrix](matrix.md)を使います．

## linear

```cpp
(1) vector<double> linear_real(Matrix<double> a, vector<double> b)
(2) vector<modint> linear_mod(Matrix<modint> a, vector<modint> b)
```

$a\boldsymbol{x} = \boldsymbol{b}$ の解のうち $1$ つを返します．解が存在しない場合，空の `vector` を返します．

**制約**

- `a` は正方行列
- `a` の列数と `b` のサイズが等しい

**計算量**

$h, w$ を `a` の行数と列数として

- $O(h \times w^2)$

