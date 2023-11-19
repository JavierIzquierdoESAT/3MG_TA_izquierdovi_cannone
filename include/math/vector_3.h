#ifndef __VEC3_H__
#define __VEC3_H__ 1

#include <math.h>

#include "math/math_utils.h"
namespace coma {
class Vec3 {
 public:
  Vec3();
  Vec3(float value);
  Vec3(float x, float y, float z);
  Vec3(float* values_array);
  Vec3(const Vec3& other);
  ~Vec3();

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator+(float value) const;
  Vec3& operator+=(const Vec3& other);
  Vec3& operator+=(float value);
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator-(float value) const;
  Vec3& operator-=(const Vec3& other);
  Vec3& operator-=(float value);
  bool operator==(const Vec3& other) const;
  bool operator!=(const Vec3& other) const;
  void operator=(const Vec3& other);
  void operator=(float value);
  Vec3 operator*(float value) const;
  Vec3& operator*=(float value);
  Vec3 operator/(float value) const;
  Vec3& operator/=(float value);

  float Magnitude() const;
  Vec3 Normalized() const;
  void Normalize();
  float SqrMagnitude() const;
  void Scale(const Vec3& other);

  static Vec3 Lerp(const Vec3& a, const Vec3& b, float t);
  static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, float t);
  static float DotProduct(const Vec3& a, const Vec3& b);
  static float Angle(const Vec3& a, const Vec3& b);
  static Vec3 CrossProduct(const Vec3& a, const Vec3& b);
  static float Distance(const Vec3& a, const Vec3& b);
  static Vec3 Reflect(const Vec3& direction, const Vec3& normal);

  static const Vec3 up;
  static const Vec3 down;
  static const Vec3 right;
  static const Vec3 left;
  static const Vec3 forward;
  static const Vec3 back;
  static const Vec3 zero;
  static const Vec3 unit;

  float x;
  float y;
  float z;
};

inline float Vec3::Magnitude() const { return sqrtf(x * x + y * y + z * z); }

inline void Vec3::Normalize() { *this /= Magnitude(); }

inline Vec3 Vec3::Normalized() const { return Vec3(*this / Magnitude()); }

inline float Vec3::DotProduct(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vec3::Angle(const Vec3& a, const Vec3& b) {
  return acosf(DotProduct(a, b) / (a.Magnitude() * b.Magnitude()));
}

inline Vec3 Vec3::CrossProduct(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

inline float Vec3::SqrMagnitude() const { return x * x + y * y + z * z; }

inline void Vec3::Scale(const Vec3& other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
}

inline Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, float t) {
  t = t > 1 ? 1 : t;
  t = t < 0 ? 0 : t;
  return (b - a) * t + a;
}

inline Vec3 Vec3::LerpUnclamped(const Vec3& a, const Vec3& b, float t) {
  return (b - a) * t + a;
}

inline float Vec3::Distance(const Vec3& a, const Vec3& b) {
  return (b - a).Magnitude();
}

inline Vec3 Vec3::Reflect(const Vec3& direction, const Vec3& normal) {
  Vec3 nn = normal.Normalized();
  return direction - nn * 2 * DotProduct(direction, nn);
}

inline Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

inline Vec3 Vec3::operator+(float value) const {
  return Vec3(x + value, y + value, z + value);
}

inline Vec3& Vec3::operator+=(const Vec3& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

inline Vec3& Vec3::operator+=(float value) {
  x += value;
  y += value;
  z += value;
  return *this;
}

inline Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

inline Vec3 Vec3::operator-(float value) const {
  return Vec3(x - value, y - value, z - value);
}

inline Vec3& Vec3::operator-=(const Vec3& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

inline Vec3& Vec3::operator-=(float value) {
  x -= value;
  y -= value;
  z -= value;
  return *this;
}

inline bool Vec3::operator==(const Vec3& other) const {
  if (x == other.x && y == other.y && z == other.z) return true;
  return false;
}

inline bool Vec3::operator!=(const Vec3& other) const {
  if (x == other.x && y == other.y && z == other.z) return false;
  return true;
}

inline void Vec3::operator=(const Vec3& other) {
  x = other.x;
  y = other.y;
  z = other.z;
}

inline void Vec3::operator=(float value) {
  x = value;
  y = value;
  z = value;
}

inline Vec3 Vec3::operator*(float value) const {
  return Vec3(x * value, y * value, z * value);
}

inline Vec3& Vec3::operator*=(float value) {
  x *= value;
  y *= value;
  z *= value;
  return *this;
}

inline Vec3 Vec3::operator/(float value) const {
  return Vec3(x / value, y / value, z / value);
}

inline Vec3& Vec3::operator/=(float value) {
  x /= value;
  y /= value;
  z /= value;
  return *this;
}
}  // namespace coma
#endif
