#ifndef __VEC2_H__
#define __VEC2_H__ 1

#include <math.h>

class Vec2 {
 public:

  Vec2();
  Vec2(float x, float y);
  Vec2(const Vec2& copy);
  ~Vec2();

  Vec2 operator+(const Vec2& other) const;
  Vec2 operator+(float value);
  Vec2& operator+=(const Vec2& other);
  Vec2& operator+=(float value);
  Vec2 operator-(const Vec2& other) const;
  Vec2 operator-(float value) const;
  Vec2 operator-() const;
  Vec2& operator-=(const Vec2& other);
  Vec2& operator-=(float value);
  bool operator==(const Vec2& other) const;
  bool operator!=(const Vec2& other) const;
  void operator=(const Vec2& other);
  void operator=(float value);
  Vec2 operator*(float value) const;
  Vec2& operator*=(float value);
  Vec2 operator/(float value) const;
  Vec2& operator/=(float value);

  float Magnitude() const;
  void Normalize();
  Vec2 Normalized() const;

  void Scale(const Vec2 scale);

  float SqrMagnitude() const;
  static float Distance(const Vec2 a, const Vec2 b);

  static float DotProduct(Vec2 a, Vec2 b);

  static Vec2 Lerp(const Vec2 a, const Vec2 b, float t);
  static Vec2 LerpUnclamped(const Vec2 a, const Vec2 b, float t);

  static float Radians(const Vec2 v);

  static const Vec2 up;
  static const Vec2 down;
  static const Vec2 right;
  static const Vec2 left;
  static const Vec2 zero;
  static const Vec2 one;

  float x;
  float y;
};


inline Vec2 Vec2::operator+(const Vec2& other) const {
  return Vec2(x + other.x, y + other.y);
}

inline Vec2 Vec2::operator+(float value) {
  return Vec2(x + value, y + value);
}

inline Vec2& Vec2::operator+=(const Vec2& other){
  x += other.x;
  y += other.y;
  return *this;
}

inline Vec2& Vec2::operator+=(float value){
  x += value;
  y += value;
  return *this;
}

inline Vec2 Vec2::operator-(const Vec2& other) const {
  return Vec2(x - other.x, y - other.y);
}

inline Vec2 Vec2::operator-(float value) const {
  return Vec2(x - value, y - value);
}

inline Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

inline Vec2& Vec2::operator-=(const Vec2& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

inline Vec2& Vec2::operator-=(float value){
  x -= value;
  y -= value;
  return *this;
}

inline bool Vec2::operator==(const Vec2& value) const {
  if(x == value.x && y == value.y) return true;
  return false;
}

inline bool Vec2::operator!=(const Vec2& value) const {
  if(x == value.x && y == value.y) return false;
  return true;
}


inline void Vec2::operator=(const Vec2& other) {
  x = other.x;
  y = other.y;
}

inline void Vec2::operator=(float value) {
  x = value;
  y = value;
}

inline Vec2 Vec2::operator*(float value) const {
  return Vec2(x * value, y * value);
}

inline Vec2& Vec2::operator*=(float value) { 
  x *= value;
  y *= value;
  return *this;
}

inline Vec2 Vec2::operator/(float value) const {
	return Vec2(x / value, y / value);
}

inline Vec2& Vec2::operator/=(float value) {
  x /= value;
  y /= value;
	return *this;
}

inline float Vec2::Magnitude() const {
  return sqrtf(x * x + y * y);
}

inline void Vec2::Normalize() {
  if(Magnitude() != 0)
    *this /= Magnitude();
}

inline Vec2 Vec2::Normalized() const {
  float mag = Magnitude();
  if(mag==0) return Vec2(0,0);
  return Vec2(x/mag, y/mag);
}

inline void Vec2::Scale(const Vec2 scale){
  x *= scale.x;
  y *= scale.y;
}

inline float Vec2::SqrMagnitude() const {
  return x * x + y * y;
}


inline float Vec2::Distance(const Vec2 a, const Vec2 b) {
  return (b - a).Magnitude();
}

inline Vec2 Vec2::Lerp(const Vec2 a, const Vec2 b, float t) {
  t = t > 1 ? 1 : t;
  t = t < 0 ? 0 : t;
  return (b - a) * t + a;
}

inline Vec2 Vec2::LerpUnclamped(const Vec2 a, const Vec2 b, float t) {
	return (b - a) * t + a;
}

inline float Vec2::Radians(const Vec2 v){
  return atan2f(v.y, v.x);
}

inline float Vec2::DotProduct(Vec2 a, Vec2 b) {
	return a.x*b.x + a.y*b.y;
}

#endif 
