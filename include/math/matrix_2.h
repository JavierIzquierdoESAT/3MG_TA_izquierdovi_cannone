//--------------------------------------------------------------//
//  Math Library
//  Matrix 2 Class Definition.
//--------------------------------------------------------------//
//
//   m0 m1
//   m2 m3
//
//--------------------------------------------------------------//

#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include "math/vector_2.h"

class Mat2 {
 public:
  Mat2();
  Mat2(float a[4]);
  Mat2(float value);
  Mat2(const Vec2& a, const Vec2& b);
  Mat2(const Mat2& copy);
  ~Mat2();
  Mat2 Identity() const;
  Mat2 Multiply(const Mat2& other) const;
  float Determinant() const;
  Mat2 Adjoint() const;
  Vec2 GetLine(int line) const;
  Vec2 GetColum(int line) const;

  Mat2 Inverse() const;
  Mat2 Transpose() const;

  inline Mat2 operator+(const Mat2& other) const;
  inline void operator+=(const Mat2& other);
  inline Mat2 operator+(float value) const;
  inline void operator+=(float value);
  inline Mat2 operator-(const Mat2& other) const;
  inline void operator-=(const Mat2& other);
  inline Mat2 operator-(float value) const;
  inline void operator-=(float value);

  inline Mat2 operator*(float value) const;
  inline void operator*=(float value);
  inline Mat2 operator/(float value) const;
  inline void operator/=(float value);

  bool operator==(const Mat2& other) const;
  bool operator!=(const Mat2& other) const;
  inline void operator=(const Mat2& other);

  float m[4];
};

inline Mat2 Mat2::operator+(const Mat2& other) const {
  Mat2 res;
  for (int i = 0; i < 4; i++) {
    res.m[i] = m[i] + other.m[i];
  }
  return res;
}

inline void Mat2::operator+=(const Mat2& other) {
  for (int i = 0; i < 4; i++) {
    m[i] += other.m[i];
  }
}

inline Mat2 Mat2::operator+(float value) const {
  Mat2 res;
  for (int i = 0; i < 4; i++) {
    res.m[i] = m[i] + value;
  }
  return res;
}

inline void Mat2::operator+=(float value) {
  for (int i = 0; i < 4; i++) {
    m[i] += value;
  }
}

inline Mat2 Mat2::operator-(const Mat2& other) const {
  Mat2 res;
  for (int i = 0; i < 4; i++) {
    res.m[i] = m[i] - other.m[i];
  }
  return res;
}

inline void Mat2::operator-=(const Mat2& other) {
  for (int i = 0; i < 4; i++) {
    m[i] -= other.m[i];
  }
}

inline Mat2 Mat2::operator-(float value) const {
  Mat2 res;
  for (int i = 0; i < 4; i++) {
    res.m[i] = m[i] - value;
  }
  return res;
}

inline void Mat2::operator-=(float value) {
  for (int i = 0; i < 4; i++) {
    m[i] -= value;
  }
}

inline Mat2 Mat2::operator*(float value) const {
  Mat2 res;
  for (int i = 0; i < 4; i++) {
    res.m[i] = m[i] * value;
  }
  return res;
}

inline void Mat2::operator*=(float value) {
  for (int i = 0; i < 4; i++) {
    m[i] *= value;
  }
}

inline Mat2 Mat2::operator/(float value) const {
  Mat2 res;
  for (int i = 0; i < 4; i++) {
    res.m[i] = m[i] / value;
  }
  return res;
}

inline void Mat2::operator/=(float value) {
  for (int i = 0; i < 4; i++) {
    m[i] /= value;
  }
}

inline bool Mat2::operator==(const Mat2& other) const {
  for (int i = 0; i < 4; i++) {
    if (m[i] != other.m[i]) return false;
  }
  return true;
}

inline bool Mat2::operator!=(const Mat2& other) const {
  for (int i = 0; i < 4; i++) {
    if (m[i] != other.m[i]) return true;
  }
  return false;
}

inline void Mat2::operator=(const Mat2& other) {
  for (int i = 0; i < 4; i++) {
    m[i] = other.m[i];
  }
}

inline Mat2 Mat2::Identity() const { return Mat2(Vec2(1, 0), Vec2(0, 1)); }

inline float Mat2::Determinant() const { return m[0] * m[3] - m[1] * m[2]; }

inline Mat2 Mat2::Inverse() const {
  float det = this->Determinant();
  Mat2 res = this->Adjoint() / det;
  return res;
}

inline Mat2 Mat2::Multiply(const Mat2& other) const {
  Mat2 res;
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 2; col++) {
      res.m[row * 2 + col] = m[row * 2 + 0] * other.m[0 * 2 + col] +
                             m[row * 2 + 1] * other.m[1 * 2 + col] +
                             m[row * 2 + 2] * other.m[2 * 2 + col];
    }
  }
  return res;
}

inline Mat2 Mat2::Adjoint() const {
  return Mat2(Vec2(m[3], -m[1]), Vec2(-m[2], m[0]));
}

inline Mat2 Mat2::Transpose() const {
  return Mat2(Vec2(m[0], m[2]), Vec2(m[1], m[3]));
}

inline Vec2 Mat2::GetLine(int line) const {
  return Vec2(m[line * 2 + 0], m[line * 2 + 1]);
}

inline Vec2 Mat2::GetColum(int line) const {
  return Vec2(m[line], m[2 + line]);
}

#endif
