
#include "math/matrix_2.h"
using namespace coma;
//Constructors
Mat2::Mat2() {
  for (int i = 0; i < 4; ++i) {
    m[i] = 0;
  }
}

Mat2::Mat2(float a[4]) {
  for (int i = 0; i < 4; ++i) {
    m[i] = a[i];
  }
}

Mat2::Mat2(float a) {
  for (int i = 0; i < 4; ++i) {
    m[i] = a;
  }
}

Mat2::Mat2(const Vec2& a, const Vec2& b) {
  m[0] = a.x;
  m[1] = a.y;
  m[2] = b.x;
  m[3] = b.y;
}

Mat2::Mat2(const Mat2& copy) {
  for (int i = 0; i < 4; ++i) {
    m[i] = copy.m[i];
  }
}

Mat2::~Mat2() {
}
