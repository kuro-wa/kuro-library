[TOC]

# Union-Find Tree

無向グラフに対して，

- 辺の追加
- $2$ 頂点が連結かの判定

をならし $O(\alpha(n))$ 時間で処理することが出来ます．$\alpha(n)$ はアッカーマン関数の逆関数です．

また，内部的に各連結成分ごとに代表となる頂点を $1$ つ持っています．辺の追加により連結成分がマージされるとき，新たな代表元は元の連結成分の代表元のうちどちらかになります．

## コンストラクタ

```cpp
void op(T& a, T& b);

(1) UnionFind d(int n)
(2) UnionFind<T, op> d(int n)
(3) UnionFind<T, op> d(vector<T>& v)
```

- (1): `n` 頂点 $0$ 辺の無向グラフを作ります．

- (2): `n` 頂点 $0$ 辺の無向グラフを作ります．各連結成分がデータを持ちます．

  - データの型 `T`
  - 頂点 `a` が属する連結成分 (こちらの代表元を引き継ぐ) に頂点  `b` が属する連結成分をマージするときの操作 `op`

  を定義する必要があります．例を[連結成分のデータの例](#ex)に示しました．データはデフォルトコンストラクタで初期化されます．
- (3): `n = v.size` 頂点 $0$ 辺の無向グラフを作ります．各連結成分がデータを持ちます．(2) と同様に `T` と `op` を定義する必要があります．`v` の内容がデータの初期値となります．

**制約**

- $0 \leq n \leq 10^8$

**計算量**

- $O(n)$

## データの取得

```cpp
T& d[int a]
```

頂点 `a` が属する連結成分のデータを返します．

**制約**

- $0 \leq a < n$

**計算量**

- ならし $O(\alpha(n))$
## merge

```cpp
int d.merge(int a, int b)
```

頂点 `a` と頂点 `b` を結ぶ辺を追加します．

`a` と `b` が連結だった場合はその代表元，非連結だった場合は新たな代表元を返します．

**制約**

- $0 \leq a < n$
- $0 \leq b < n$

**計算量**

$f(n)$ を `op` の計算量として

- ならし $O(\alpha(n) \cdot f(n))$

## same

```cpp
bool d.same(int a, int b)
```

頂点 `a`, `b` が連結かどうかを返します．

**制約**

- $0 \leq a < n$
- $0 \leq b < n$

**計算量**

- ならし $O(\alpha(n))$

## leader

```cpp
int d.leader(int a)
```

頂点 `a` の属する連結成分の代表元を返します．

**制約**

- $0 \leq a < n$

**計算量**

- ならし $O(\alpha(n))$

## size

```cpp
int d.size(int a)
```

頂点 `a​` が属する連結成分のサイズを返します．

**制約**

- $0 \leq a < n$

**計算量**

- ならし $O(\alpha(n))$

## groups

```cpp
vector<vector<int>> d.groups()
```

グラフを連結成分に分け，その情報を返します．

返り値は「「一つの連結成分の頂点番号のリスト」のリスト」です．
(内側外側限らず) `vector` 内でどの順番で頂点が格納されているかは未定義です．

**計算量**

- $O(n)$

## private変数，private関数

```cpp
int _n;
vector<int> d;
vector<T> data;
```

- `_n` : 頂点数
- `d` : `d[i] < 0` ならば頂点 `i` はサイズ `-d[i]` の連結成分の代表元，`d[i] >= 0` ならば頂点 `i` の親は `d[i]`
- `data` : 自身が代表元であるときの連結成分のデータ

## 連結成分のデータの例<a name="ex"></a>

- 最小値

  ```cpp
  using T = int;
  void op(T& a, T& b) {
    a = min(a, b);
  }
  ```

- 最大値

  ```cpp
  using T = int;
  void op(T& a, T& b) {
    a = min(a, b);
  }
  ```

- 属性 `key` をもつ頂点の数 `num`

  ```cpp
  using S = map<int, int>;
  void op(S& a, S& b) {
    for (auto [key, num] : b) {
      a[key] += num;
    }
    b.clear();
  }
  ```

  

