
#include "math/matrix_3.h"

Mat3::Mat3() {
  for (int i = 0; i < 9; i++){
    m[i]=0;
  }
}

Mat3::Mat3(float value) {
  for (int i = 0; i < 9; i++){
    m[i]=value;
  }
}

Mat3::Mat3(float* values_array) {
  for (int i = 0; i < 9; i++){
    m[i]=values_array[i];
  }
}

Mat3::Mat3(Vec3 a, Vec3 b, Vec3 c) {
  m[0] = a.x; m[1] = a.y; m[2] = a.z;
  m[3] = b.x; m[4] = b.y; m[5] = b.z;
  m[6] = c.x; m[7] = c.y; m[8] = c.z;
}

Mat3::Mat3(const Mat3& copy) {
  for (int i = 0; i < 9; i++){
    m[i]=copy.m[i];
  }
}

Mat3::~Mat3() {
}

