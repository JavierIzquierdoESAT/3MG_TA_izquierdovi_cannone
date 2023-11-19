#include "math/vector_4.h"
using namespace coma;
const Vec4 Vec4::one = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
const Vec4 Vec4::zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

Vec4::Vec4() { 
  x = 0;
	y = 0;
	z = 0;
  w = 0;
}

Vec4::Vec4(float a, float b, float c, float d) {
  x = a;
  y = b;
  z = c;
  w = d;
}

Vec4::Vec4(Vec3 a, float b) {
  x = a.x;
  y = a.y;
  z = a.z;
  w = b;
}

Vec4::Vec4(float a) {
  x = a;
  y = a;
  z = a;
  w = a;
}

Vec4::Vec4(float* values_array) {
  x = values_array[0];
  y = values_array[1];
  z = values_array[2];
  w = values_array[3];
}

Vec4::Vec4(const Vec4& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
}

Vec4::~Vec4() {}
