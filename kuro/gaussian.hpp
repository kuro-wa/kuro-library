#ifndef KURO_GAUSSIAN_HPP
#define KURO_GAUSSIAN_HPP 1

#include <kuro/matrix>

namespace kuro {

// Solves real simultaneous linear equation ax=b
vector<double> linear_real(Matrix<double> a, vector<double> b) {
  constexpr double eps = 1e-10;
  int h = a.h(), w = a.w();
  assert(w == (int)b.size());
  int r = 0;
  vector<int> ids;
  for (int j = 0; j < w; ++j) {
    for (int i = r+1; i < h; ++i) {
      double d = sqrt(a[r][j]*a[r][j]+a[i][j]*a[i][j]);
      if (abs(d) < eps) continue;
      double c = a[r][j]/d, s = a[i][j]/d;
      auto rot = [&](double& u, double& v) {
        tie(u, v) = make_pair(c*u+s*v, c*v-s*u);
      };
      rot(b[r], b[i]);
      for (int k = j; k < w; ++k) rot(a[r][k], a[i][k]);
    }
    if (abs(a[r][j]) < eps) continue;
    ++r;
    ids.emplace_back(j);
    if (r == h) break;
  }
  for (int i = r; i < h; ++i) {
    if (abs(b[i]) > eps) return {};
  }
  vector<double> res(w);
  for (int i = r-1; i >= 0; --i) {
    int c = ids[i];
    res[c] = b[i];
    for (int j = c+1; j < w; ++j) {
      res[c] -= a[i][j]*res[j];
    }
    res[c] /= a[i][c];
  }
  return res;
}

// Solves mod simultaneous linear equation ax=b
template<typename Mint>
vector<Mint> linear_mod(Matrix<Mint> a, vector<Mint> b) {
  int h = a.h(), w = a.w();
  int r = 0;
  vector<int> ids;
  for (int j = 0; j < w; ++j) {
    int mi = -1;
    for (int i = r; i < h; ++i) {
      if (a[i][j]) {
        mi = i;
        break;
      }
    }
    if (mi == -1) continue;
    if (r != mi) swap(a[r], a[mi]);
    swap(b[r], b[mi]);
    for (int i = r + 1; i < h; ++i) {
      if (!a[i][j]) continue;
      auto freq = a[i][j] / a[r][j];
      for (int k = j; k < w; ++k) a[i][k] -= freq*a[r][k];
      b[i] -= freq*b[r];
    }
    ++r;
    ids.emplace_back(j);
    if (r == h) break;
  }
  for (int i = r; i < h; ++i) {
    if (!b[i]) return {};
  }
  vector<Mint> res(w);
  for (int i = r - 1; i >= 0; --i) {
    int c = ids[i];
    res[c] = b[i];
    for (int j = c + 1; j < w; ++j) {
      res[c] -= a[i][j]*res[j];
    }
    res[c] /= a[i][c];
  }
  return res;
}

} // namespace kuro
#endif  // KURO_GAUSSIAN_HPP