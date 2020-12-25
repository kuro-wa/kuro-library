#ifndef KURO_GEOMETRY_HPP
#define KURO_GEOMETRY_HPP 1

namespace kuro {

const double eps = 1e-10;
bool equal(double a, double b) { return abs(a-b) < eps;}

// 2D vector
template<typename T>
struct Point {
  T x, y;
  Point(T x=T(0), T y=T(0)) : x(x), y(y) {}
  Point operator+(const Point& p) const { return Point(x+p.x, y+p.y);}
  Point operator-(const Point& p) const { return Point(x-p.x, y-p.y);}
  Point operator*(T a) const { return Point(x*a, y*a);}
  friend Point operator*(T a, const Point& p) { return p*a;}
  friend ostream& operator<<(ostream& os, const Point& p) { return os<<'('<<p.x<<','<<p.y<<')';}
  friend istream& operator>>(istream& is, Point& p) { return is>>p.x>>p.y;}
  T dot(const Point& p) { return x*p.x+y*p.y;}
  T cross(const Point& p) {return x*p.y-y*p.x;}
  double norm() { return sqrt(x*x+y*y);}
  T sqnorm() { return x*x+y*y;}
  Point rot90() { return Point(-y, x);}
};
using P = Point<double>;

// Line Segment
struct Line {
  P s, t;
  Line(P s=P(), P t=P()) : s(s), t(t) {}
  bool on(const P& p) {
    return equal((s-p).cross(t-p), 0) && (s-p).dot(t-p) < eps;
  }
  P intersection(const Line& l) {
    return s+(l.s-s).cross(l.t-l.s)/(t-s).cross(l.t-l.s)*(t-s);
  }
  bool parallel(const Line& l) { return equal((t-s).cross(l.t-l.s), 0);}
};

// Circle
struct Circle {
  P o;
  double r;
  Circle(P o=P(), double r=0) : o(o), r(r) {}
  vector<P> intersections(const Circle& c) {
    P v = c.o-o;
    double d = v.norm();
    if (equal(d, 0)) return {};
    if (equal(d+r+c.r, max({d, r, c.r})*2)) {
      if (equal(d+r, c.r)) return {o-v*(r/d)};
      else return {o+v*(r/d)};
    }
    if (d+r+c.r < max({d, r, c.r})*2) return {};
    double x = (d*d+r*r-c.r*c.r)/(2*d);
    double y = sqrt(r*r-x*x);
    P leg = o+v*(x/d);
    v = v.rot90();
    return {leg+v*(y/d), leg-v*(y/d)};
  }
  bool include(const P& p) {
    return (p-o).sqnorm() < r*r+eps;
  }
  bool include(const Circle& c) {
    return c.r < r+eps && (c.o-o).sqnorm() < (r-c.r)*(r-c.r)+eps;
  }
};

} // namespace kuro
#endif  // KURO_GEOMETRY_HPP