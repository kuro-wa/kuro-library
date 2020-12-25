#ifndef KURO_MATRIX_HPP
#define KURO_MATRIX_HPP 1

namespace kuro {

template<typename T>
using MatrixBase = vector<vector<T>>;

template<typename T> T _zero() { return T(0);}
template<typename T> T _one() { return T(1);}

// Matrix
template<typename T, T (*zero)()=_zero<T>, T (*one)()=_one<T>>
struct Matrix : MatrixBase<T> {
  using MatrixBase<T>::MatrixBase;
  using MatrixBase<T>::size;
 public:
  int h() const { return (int)size();}
  int w() const { return (int)(*this)[0].size();}
  Matrix& operator+=(const Matrix& rhs) {
    assert(h() == rhs.h() && w() == rhs.w());
    for (int i = 0; i < h(); ++i) {
      for (int j = 0; j < w(); ++j) {
        (*this)[i][j] = (*this)[i][j]+rhs[i][j];
      }
    }
    return *this;
  }
  Matrix& operator-=(const Matrix& rhs) {
    assert(h() == rhs.h() && w() == rhs.w());
    for (int i = 0; i < h(); ++i) {
      for (int j = 0; j < w(); ++j) {
        (*this)[i][j] = (*this)[i][j]-rhs[i][j];
      }
    }
    return *this;
  }
  Matrix& operator*=(const Matrix& rhs) { return *this = *this*rhs;}
  Matrix& operator*=(const T& a) {
    for (int i = 0; i < h(); ++i) {
      for (int j = 0; j < w(); ++j) {
        (*this)[i][j] = (*this)[i][j]*a;
      }
    }
    return *this;
  }
  vector<T> operator*(const vector<T>& v) const {
    assert((int)v.size() == w());
    vector<T> res(h(), zero());
    for (int i = 0; i < h(); ++i) {
      for (int j = 0; j < w(); ++j) {
        res[i] = res[i]+(*this)[i][j]*v[j];
      }
    }
    return res;
  }
  Matrix operator+() const { return *this;}
  Matrix operator-() const { return Matrix(h(), vector<T>(w(), zero())) -= *this;}
  Matrix pow(int64_t n) const {
    assert(n >= 0);
    assert(h() == w());
    Matrix x = *this, res(h(), vector<T>(w(), zero()));
    for (int i = 0; i < h(); ++i) res[i][i] = one();
    while (n) {
      if (n&1) res *= x;
      x *= x;
      n >>= 1;
    }
    return res;
  }
  Matrix transpose() const {
    Matrix res(w(), vector<T>(h(), zero()));
    for (int i = 0; i < h(); ++i) {
      for (int j = 0; j < w(); ++j) {
        res[j][i] = *this[i][j];
      }
    }
    return res;
  }
  Matrix operator+(const Matrix& rhs) const { return Matrix(*this) += rhs;}
  Matrix operator-(const Matrix& rhs) const { return Matrix(*this) -= rhs;}
  Matrix operator*(const Matrix& rhs) const {
    assert(w() == rhs.h());
    Matrix res(h(), vector<T>(rhs.w(), zero()));
    for (int i = 0; i < h(); ++i) {
      for (int j = 0; j < rhs.w(); ++j) {
        for (int k = 0; k < w(); ++k) {
          res[i][j] = res[i][j]+(*this)[i][k]*rhs[k][j];
        }
      }
    }
    return res;
  }
  friend Matrix operator*(const T& a, const Matrix& rhs) {
    Matrix res(rhs.h(), vector<T>(rhs.w, zero()));
    for (int i = 0; i < rhs.h(); ++i) {
      for (int j = 0; j < rhs.w(); ++j) {
        res[i][j] = a*rhs[i][j];
      }
    }
    return res;
  }
  friend vector<T> operator*(const vector<T>& v, const Matrix& rhs) {
    assert((int)v.size() == rhs.h());
    vector<T> res(rhs.w(), zero());
    for (int j = 0; j < w(); ++j) {
      for (int i = 0; i < h(); ++i) {
        res[j] = res[j]+v[j]*rhs[i][j];
      }
    }
    return res;
  }
};

} // namespace kuro
#endif  // KURO_MATRIX_HPP