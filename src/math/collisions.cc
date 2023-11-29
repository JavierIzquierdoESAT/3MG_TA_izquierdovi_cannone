///@author Javier Izquierdo Vicedo
#include "math/collisions.h"
using namespace coma;
using namespace cols;

//------------------------CRICLE----------------------------
Circle::Circle() {
  pos = 0;
  radius = 0;
};

Circle::Circle(float x, float y, float r) {
  pos.x = x;
  pos.y = y;
  radius = r;
}
Circle::Circle(Vec2 posi, float r) {
  pos.x = posi.x;
  pos.y = posi.y;
  radius = r;
}
Circle::Circle(float v[3]) {
  pos.x = v[0];
  pos.y = v[1];
  radius = v[2];
}
Circle::Circle(const Circle& o) {
  pos.x = o.pos.x;
  pos.y = o.pos.y;
  radius = o.radius;
}
Circle::~Circle() {}

void Circle::operator=(const Circle& o) {
  pos.x = o.pos.x;
  pos.y = o.pos.y;
  radius = o.radius;
}

//------------------------SHPERE----------------------------
Sphere::Sphere() {
  pos = 0;
  radius = 0;
}
Sphere::Sphere(float x, float y, float z, float r) {
  pos.x = x;
  pos.y = y;
  pos.z = z;
  radius = r;
}
Sphere::Sphere(Vec3 posi, float r) {
  pos.x = posi.x;
  pos.y = posi.y;
  pos.z = posi.z;
  radius = r;
}
Sphere::Sphere(float v[4]) {
  pos.x = v[0];
  pos.y = v[1];
  pos.z = v[2];
  radius = v[3];
}
Sphere::Sphere(const Sphere& o) {
  pos.x = o.pos.x;
  pos.y = o.pos.y;
  pos.z = o.pos.z;
  radius = o.radius;
}
Sphere::~Sphere() {}

void Sphere::operator=(const Sphere& o) {
  pos.x = o.pos.x;
  pos.y = o.pos.y;
  pos.z = o.pos.z;
  radius = o.radius;
}

////------------------------"2D Checks"----------------------------
bool cols::Check(Circle c, Vec2 p) {
  bool res = false;
  if (Vec2::Distance(c.pos, p) <= c.radius) {
    res = true;
  };
  return res;
}

bool cols::Check(Circle c1, Circle c2) {
  bool res = false;
  if (Vec2::Distance(c1.pos, c2.pos) <= c1.radius + c2.radius) {
    res = true;
  };
  return res;
}

////------------------------"3D Checks"----------------------------
bool cols::Check(Sphere s, Vec3 p) {
  bool res = false;
  if (Vec3::Distance(s.pos, p) <= s.radius) {
    res = true;
  };
  return res;
}

bool cols::Check(Sphere s1, Sphere s2) {
  bool res = false;
  if (Vec3::Distance(s1.pos, s2.pos) <= s1.radius + s2.radius) {
    res = true;
  };
  return res;
}