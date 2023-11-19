#ifndef __VEC4_H__
#define __VEC4_H__ 1

#include "math/matrix_3.h"
#include "math/vector_3.h"
namespace coma {
class Vec4 {
 public:
  Vec4();
  Vec4(float x, float y, float z, float w);
  Vec4(Vec3 a, float w);
  Vec4(float a);
  Vec4(float* values_array);
  Vec4(const Vec4& other);
  ~Vec4();

  Vec4 operator+(const Vec4& other) const;
  Vec4 operator+(float value) const;
  void operator+=(const Vec4& other);
  void operator+=(float value);
  Vec4 operator-(const Vec4& other) const;
  Vec4 operator-(float value) const;
  void operator-=(const Vec4& other);
  void operator-=(float value);

  Vec4 operator*(float value) const;
  void operator*=(float value);
  Vec4 operator/(float value) const;
  void operator/=(float value);
  bool operator==(const Vec4& other);
  bool operator!=(const Vec4& other);
  void operator=(const Vec4& other);

  float Magnitude() const;
  void Normalize();
  Vec4 Normalized() const;
  void Scale(Vec4 scale);
  float SqrMagnitude() const;

  // Author: Alan Gutierrez Ramirez
  Vec4 Homogenize();

  static float Distance(const Vec4& a, const Vec4& b);
  static float DotProduct(Vec4 a, Vec4 b);
  static Vec4 Lerp(const Vec4& a, const Vec4& b, float index);

  static const Vec4 one;
  static const Vec4 zero;

  float x;
  float y;
  float z;
  float w;
};

// Author: Alan Gutierrez Ramirez
inline Vec4 Vec4::Homogenize() {
  Vec4 ans;
  if (this->w != 0) {
    float reciproca = 1.0f / this->w;
    ans *= reciproca;
  }
  return ans;
}

inline float Vec4::Magnitude() const {
  return sqrtf(x * x + y * y + z * z + w * w);
}

inline void Vec4::Normalize() { *this /= Magnitude(); }

inline Vec4 Vec4::Normalized() const { return Vec4(*this / Magnitude()); }

inline void Vec4::Scale(Vec4 other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  w *= other.w;
}

inline float Vec4::SqrMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline float Vec4::Distance(const Vec4& a, const Vec4& b) {
  return (b - a).Magnitude();
}

inline float Vec4::DotProduct(Vec4 a, Vec4 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vec4 Vec4::Lerp(const Vec4& a, const Vec4& b, float t) {
  t = t > 1 ? 1 : t;
  t = t < 0 ? 0 : t;
  return (b - a) * t + a;
}

inline Vec4 Vec4::operator+(const Vec4& other) const {
  return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

inline Vec4 Vec4::operator+(float value) const {
  return Vec4(x + value, y + value, z + value, w + value);
}

inline void Vec4::operator+=(const Vec4& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
}

inline void Vec4::operator+=(float value) {
  x += value;
  y += value;
  z += value;
  w += value;
}

inline Vec4 Vec4::operator-(const Vec4& other) const {
  return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

inline Vec4 Vec4::operator-(float value) const {
  return Vec4(x - value, y - value, z - value, w - value);
}

inline void Vec4::operator-=(const Vec4& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
}

inline void Vec4::operator-=(float value) {
  x -= value;
  y -= value;
  z -= value;
  w -= value;
}

inline Vec4 Vec4::operator*(float value) const {
  return Vec4(x * value, y * value, z * value, w * value);
}

inline void Vec4::operator*=(float value) {
  x *= value;
  y *= value;
  z *= value;
  w *= value;
}

inline Vec4 Vec4::operator/(float value) const {
  return Vec4(x / value, y / value, z / value, w / value);
}

inline void Vec4::operator/=(float value) {
  x /= value;
  y /= value;
  z /= value;
  w /= value;
}

inline bool Vec4::operator==(const Vec4& other) {
  if (x == other.x && y == other.y && z == other.z && w == other.w) return true;
  return false;
}
inline bool Vec4::operator!=(const Vec4& other) {
  if (x == other.x && y == other.y && z == other.z && w == other.w)
    return false;
  return true;
}
inline void Vec4::operator=(const Vec4& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
}
}  // namespace coma
#endif
