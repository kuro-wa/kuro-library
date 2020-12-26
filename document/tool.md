[TOC]

# Tool

便利関数詰め合わせです．`T` はクラステンプレートです．

## chmin, chmax

```cpp
bool chmin(T& x, const T& y)
bool chmax(T& x, const T& y)
```

`x` と `y` を比較し，

- `chmin` : $x > y$ のとき
- `chmax` : $x < y$ のとき

`x` に `y` を代入し，`true` を返します．それ以外のとき `false` を返します．`x` を更新したかどうかを返すと言い換えられます．

**計算量**

- 比較演算子の計算量と同じ

## 座標圧縮

```cpp
vector<T> compress(vector<T> v)
map<T, int> dict(const vector<T> &v)
```

- `compress` : 座標の重複を取り除き，昇順に並べ替えたものを返します．
- `dict` : 元の座標が，圧縮後に何番目にあるかを返します．

**計算量**

- ソートの計算量と同じ
