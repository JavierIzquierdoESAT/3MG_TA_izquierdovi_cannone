///@author javier Izquierdo Vicedo
#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__ 1

#include "math/vector_2.h"
#include "math/vector_3.h"
#include "math/vector_4.h"

namespace coma {
namespace cols {

class Circle {
 public:
  Circle();
  Circle(float x, float y, float r);
  Circle(Vec2 pos, float r);
  Circle(float v[3]);
  Circle(const Circle& o);
  ~Circle();

  void operator=(const Circle& o);

  float radius;
  Vec2 pos;
};

class Sphere {
 public:
  Sphere();
  Sphere(float x, float y, float z, float r);
  Sphere(Vec3 pos, float r);
  Sphere(float v[4]);
  Sphere(const Sphere& o);
  ~Sphere();

  void operator=(const Sphere& o);

  float radius;
  Vec3 pos;
};

class Rect2 {
  Rect2();
  Rect2(float x, float y, float w, float h);
  Rect2(float a[4]);
  Rect2(const Vec4& a);
  Rect2(const Vec2& pos, const Vec2& size);
  Rect2(const Rect2& o);
  ~Rect2();

  float r[4];
};

class Rect3 {
  Rect3();
  Rect3(float x, float y, float z, float w, float h, float d);
  Rect3(float a[6]);
  Rect3(const Vec3& pos, const Vec3& size);
  Rect3(const Rect3& o);
  ~Rect3();

  float r[6];
};

class Obb2 {};
class Obb3 {};

// 2d
bool Check(Circle c, Vec2 p);
bool Check(Rect2 r, Vec2 p);
bool Check(Obb2 o, Vec2 p);

bool Check(Circle c1, Circle c2);
bool Check(Rect2 r, Circle c);
bool Check(Obb2 o, Circle c);

bool Check(Rect2 r1, Rect2 r2);
bool Check(Obb2 o, Rect2 r);

bool Check(Obb2 o1, Obb2 o2);

// 3d
bool Check(Sphere s, Vec3 p);
bool Check(Rect3 r, Vec3 p);
bool Check(Obb3 o, Vec3 p);

bool Check(Sphere s1, Sphere s2);
bool Check(Rect3 r, Sphere s);
bool Check(Obb3 o, Sphere s);

bool Check(Rect3 r1, Rect3 r2);
bool Check(Obb3 o, Rect3 r);

bool Check(Obb3 o1, Obb3 o2);
}  // namespace cols
}  // namespace coma

#endif
