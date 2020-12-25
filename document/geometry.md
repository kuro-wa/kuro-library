[TOC]

# Geometry

幾何学図形詰め合わせです．

## 定数

```cpp
const double eps = 1e-10
```

## 比較関数

```cpp
bool equal(double a, double b)
```

## Point

```cpp
struct Point {
  T x, y;
  T dot(const Point& p);
  T cross(const Point& p);
  double norm();
  T sqnorm();
  Point rot90();
};
```

$2$ 次元ベクトルです．点として扱います．`P` が `Point<double>` のエイリアスになっています．

- `x, y` : $x$ 座標と $y$ 座標
- `dot` : 内積
- `cross` : 外積
- `norm` : ノルム
- `sqnorm` : ノルムの $2$ 乗 (高速化用)
- `rot90` : 反時計回りの $90$ 度回転

**コンストラクタ**

```cpp
Point<T>(T x=T(0), T y=T(0))
```

型 `T` と座標 `x, y` を指定します．

**演算子**

```cpp
Point + Point = Point
Point - Point = Point
Point * T = Point
T * Point = Point

istream >> Point
ostream << Point // (x,y)
```

## Line

```cpp
struct Line {
  P s, t;
  bool on(const P& p);
  P intersection(const Line& l);
  bool parallel(const Line& l);
};
```

線分です．

- `s, t` : 端点
- `on` : 線分上に点 `p` があるか (端点を含む)
- `intersection` : 自身と線分 `l` を直線に延長したときの交点 (平行のとき，エラー)
- `parallel` : 線分 `l` と平行か

**コンストラクタ**

```cpp
Line(P s=P(), P t=P())
```

端点を指定します．

## Circle

```cpp
struct Circle {
  P o;
  double r;
  vector<P> intersections(const Circle& c);
  bool include(const P& p);
  bool include(const Circle& c);
};
```

円です．

- `o` : 中心
- `r` : 半径
- `intersection` : 円 `c` との交点 ($0$ から $2$ 個)
- `include` : 点 `p` あるいは円 `c` を完全に内部に含むか (円周上も含む)

**コンストラクタ**

```cpp
Circle(P o=P(), double r=0)
```

中心と半径を指定します．
