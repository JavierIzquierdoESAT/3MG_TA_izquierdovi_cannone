#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "math/vector_3.h"
#include "math/vector_4.h"
#include "math/matrix_3.h"
#include <math.h>
class Mat4 {
 public:

  Mat4();
  Mat4(float a[16]);
  Mat4(float value);
  Mat4(const Mat4& copy);
  ~Mat4();

  Mat4 Identity() const;
  Mat4 Multiply(const Mat4& other) const;

  float Determinant() const;
  Mat4 Adjoint() const;
  bool GetInverse(Mat4* out) const;
  bool Inverse();

  Mat4 Transpose() const;

  Mat3 getSubMatrix(int r, int c) const;

  static Mat4 Translate(const Vec3& distance);
  static Mat4 Translate(float x, float y, float z);

  static Mat4 Scale(const Vec3& scale);
  static Mat4 Scale(float x, float y, float z);

  static Mat4 RotateX(float radians);
  static Mat4 RotateY(float radians);
  static Mat4 RotateZ(float radians);

  static Mat4 GetTransform(const Vec3& translate, const Vec3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Mat4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Vec4 Transform(const Vec4& v);

  //Author: Alan Gutierrez Ramirez
  Mat4 Projection() const;
  //Author: Alan Gutierrez Ramirez
  Vec3 TransformVec3(Vec3 *vector);


  Mat4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Mat4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  Vec4 GetColum(int colum) const;
  Vec4 GetLine(int line) const;

  Mat4 operator+(const Mat4& other) const;
  Mat4& operator+=(const Mat4& other);
  Mat4 operator+(float value) const;
  Mat4& operator+=(float value);
  Mat4 operator-(const Mat4& other) const;
  Mat4& operator-=(const Mat4& other);
  Mat4 operator-(float value) const;
  Mat4& operator-=(float value);
  Mat4& operator*=(float value);
  Mat4 operator*(float value) const;
  Mat4& operator/=(float value);
  Mat4 operator/(float value) const;
  bool operator==(const Mat4& other);
  bool operator!=(const Mat4& other);
  void operator=(const Mat4& other);

  float m[16];
};

//Author: Alan Gutierrez Ramirez
inline Mat4 Mat4::Projection() const
{
  float s[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 1.0f,
                 0.0f, 0.0f, 0.0f, 0.0f};
  return Mat4(s);
}
// Author: Alan Gutierrez Ramirez
inline Vec3 Mat4::TransformVec3(Vec3 *vector)
{
  float w = (this->m[3] * vector->x) + (this->m[7] * vector->y) + (this->m[11] * vector->z) + this->m[15];
  float s[3]{
      ((this->m[0] * vector->x) + (this->m[4] * vector->y) + (this->m[8] * vector->z) + this->m[12]) / w,
      ((this->m[1] * vector->x) + (this->m[5] * vector->y) + (this->m[9] * vector->z) + this->m[13]) / w,
      ((this->m[2] * vector->z) + (this->m[6] * vector->z) + (this->m[10] * vector->z) + this->m[14]) / w,
  };
  return Vec3(s);
}

inline Vec4 Mat4::Transform(const Vec4& v){
  float res[4];
  for (int i = 0; i < 4; i++){
    res[i] = m[i + 0*4] * v.x + m[i + 1*4] * v.y  +m[i + 2*4] * v.z + m[i + 3*4] * v.w;
  }
	return Vec4(res);
}

inline Mat4 Mat4::Identity() const
{
  float s[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
	return Mat4(s);
}

inline Mat4 Mat4::Multiply(const Mat4& other)const  {
	Mat4 res;
  for (int row = 0; row < 4; row++){
    for(int col = 0; col < 4; col++){
      res.m[row*4 + col] = 
        m[row*4 + 0] * other.m[0*4 + col] + 
        m[row*4 + 1] * other.m[1*4 + col] + 
        m[row*4 + 2] * other.m[2*4 + col] +
        m[row*4 + 3] * other.m[3*4 + col];
    }
  }
	return res;
}



inline float Mat4::Determinant() const {
  return Mat3(Vec3(m[5], m[6], m[7]), 
              Vec3(m[9], m[10], m[11]),
              Vec3(m[13], m[14], m[15])).Determinant() * m[0] +
         Mat3(Vec3(m[1], m[2], m[3]), 
              Vec3(m[9], m[10], m[11]),
              Vec3(m[13], m[14], m[15])).Determinant() * -m[4] +
         Mat3(Vec3(m[1], m[2], m[3]), 
              Vec3(m[5], m[6], m[7]),
              Vec3(m[13], m[14], m[15])).Determinant() * m[8] +
         Mat3(Vec3(m[1], m[2], m[3]), 
              Vec3(m[5], m[6], m[7]),
              Vec3(m[9], m[10], m[11])).Determinant() * -m[12];
}

inline Mat3 Mat4::getSubMatrix(int r, int c) const{
  float s[9];
  int k = 0;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if(r != i && c != j){
        s[k] = this->m[i*4 + j];
        k++;
      }
    }
  }
  return Mat3(s);
}

inline Mat4 Mat4::Adjoint() const {
  float s[16] = {
    this->getSubMatrix(0,0).Determinant(), 
    -this->getSubMatrix(0,1).Determinant(), 
    this->getSubMatrix(0,2).Determinant(),
    -this->getSubMatrix(0,3).Determinant(),

    -this->getSubMatrix(1,0).Determinant(),
    this->getSubMatrix(1,1).Determinant(),
    -this->getSubMatrix(1,2).Determinant(),
    this->getSubMatrix(1,3).Determinant(),

    this->getSubMatrix(2,0).Determinant(),
    -this->getSubMatrix(2,1).Determinant(),
    this->getSubMatrix(2,2).Determinant(),
    -this->getSubMatrix(2,3).Determinant(),

    -this->getSubMatrix(3,0).Determinant(),
    this->getSubMatrix(3,1).Determinant(),
    -this->getSubMatrix(3,2).Determinant(),
    this->getSubMatrix(3,3).Determinant(),
  };
	return Mat4(s).Transpose();
}

inline bool Mat4::Inverse() {
	float det = this->Determinant();
  if(det == 0) return false;
  operator= (this->Adjoint() / det);
	return true;
}

inline bool Mat4::GetInverse(Mat4* out) const {
  float det = this->Determinant();
  if(det == 0) return false;
  *out = (this->Adjoint() / det);
	return true;
}

inline Mat4 Mat4::Transpose() const {
  float f[16] = {
    m[0], m[4], m[8], m[12],
    m[1], m[5], m[9], m[13],
    m[2], m[6], m[10], m[14],
    m[3], m[7], m[11], m[15],
  };
  return Mat4(f);
}

inline Mat4 Mat4::Translate(const Vec3& distance){
  float f[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    distance.x, distance.y,distance.z, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::Translate(float x, float y, float z){
	float f[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    x, y, z, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::Scale(const Vec3& scale){
  float f[16] = {
    scale.x, 0, 0, 0,
    0, scale.y, 0, 0,
    0, 0, scale.z, 0,
    0, 0, 0, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::Scale(float x, float y, float z){
	float f[16] = {
    x, 0, 0, 0,
    0, y, 0, 0,
    0, 0, z, 0,
    0, 0, 0, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::RotateX(float radians){
	float f[16] = {
    1, 0, 0, 0,
    0, cosf(radians), -sinf(radians), 0,
    0, sinf(radians), cosf(radians), 0,
    0, 0, 0, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::RotateY(float radians){
	float f[16] = {
    cosf(radians), 0, sinf(radians), 0,
    0, 1, 0, 0,
    -sinf(radians), 0, cosf(radians), 0,
    0, 0, 0, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::RotateZ(float radians) {
	float f[16] = {
    cosf(radians), -sinf(radians), 0, 0,
    sinf(radians), cosf(radians), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
	return Mat4(f);
}

inline Mat4 Mat4::GetTransform(const Vec3& translate,
								const Vec3& scale,
								float rotateX, float rotateY,
								float rotateZ)   {
	return  Scale(scale).Multiply(
    RotateX(rotateX).Multiply(RotateY(rotateY)).Multiply(RotateZ(rotateZ))
  ).Multiply(Translate(translate));
}

inline Mat4 Mat4::GetTransform(float trans_x, float trans_y, float trans_z,
	float scale_x, float scale_y, float scale_z,
	float rotateX, float rotateY, float rotateZ)  {



	return
  Translate(trans_x, trans_y, trans_z)
  .Multiply(RotateX(rotateX))
  .Multiply(RotateY(rotateY))
  .Multiply(RotateZ(rotateZ))
  .Multiply(Scale(scale_x, scale_y, scale_z));
}

inline Vec4 Mat4::GetColum(int colum) const {

	return Vec4(m[0 + colum], m[4 + colum], m[8 + colum], m[12 + colum]);
}

inline Vec4 Mat4::GetLine(int line) const {
	return Vec4(m[line*4 + 0], m[line*4 + 1], m[line*4 + 2], m[line*4 + 3]);
}

inline Mat4 Mat4::PerspectiveMatrix(float fov, float aspect,
	float near, float far) const {
	fov = 0;
  aspect = 0;
  near = 0;
  far = 0;
	return Mat4();
}

inline Mat4 Mat4::OrthoMatrix(float right, float left, float top, float valueottom,
	float near, float far) const {
    right = 0;
  left = 0;
  top = 0;
  valueottom = 0;
  near = 0;
  far = 0;
	return Mat4();
}



inline Mat4 Mat4::operator+(const Mat4& other) const {
  Mat4 res;
  for (int i = 0; i < 16; i++){
    res.m[i] = m[i] + other.m[i];
  }
	return res;
}

inline Mat4& Mat4::operator+=(const Mat4& other) {
	for (int i = 0; i < 16; i++){
    m[i] += other.m[i];
  }
	return *this;
}

inline Mat4 Mat4::operator+(float value) const {
	Mat4 res;
  for (int i = 0; i < 16; i++){
    res.m[i] = m[i] + value;
  }
	return res;
}

inline Mat4& Mat4::operator+=(float value) {	
	for (int i = 0; i < 16; i++){
    m[i] += value;
  }
	return *this;
}


inline Mat4 Mat4::operator-(const Mat4& other) const  {
	Mat4 res;
  for (int i = 0; i < 16; i++){
    res.m[i] = m[i] - other.m[i];
  }
	return res;
}

inline Mat4& Mat4::operator-=(const Mat4& other) {
	for (int i = 0; i < 16; i++){
    m[i] -= other.m[i];
  }
	return *this;
}

inline Mat4 Mat4::operator-(float value) const  {
	Mat4 res;
  for (int i = 0; i < 16; i++){
    res.m[i] = m[i] - value;
  }
	return res;
}

inline Mat4& Mat4::operator-=(float value) {
	for (int i = 0; i < 16; i++){
    m[i] -= value;
  }
	return *this;
}

inline Mat4& Mat4::operator*=(float value) {
	for (int i = 0; i < 16; i++){
    m[i] *= value;
  }
	return *this;
}

inline Mat4 Mat4::operator*(float value) const  {
	Mat4 res;
  for (int i = 0; i < 16; i++){
    res.m[i] = m[i] * value;
  }
	return res;
}

inline Mat4& Mat4::operator/=(float value) {
	for (int i = 0; i < 16; i++){
    m[i] /= value;
  }
	return *this;
}

inline Mat4 Mat4::operator/(float value) const {
	Mat4 res;
  for (int i = 0; i < 16; i++){
    res.m[i] = m[i] / value;
  }
	return res;
}

inline bool Mat4::operator==(const Mat4& other) {
	for (int i = 0; i < 16; i++){
    if(m[i] != other.m[i]) return false;
  }
	return true;
}

inline bool Mat4::operator!=(const Mat4& other) {
	for (int i = 0; i < 16; i++){
    if(m[i] != other.m[i]) return true;
  }
	return false;
}

inline void Mat4::operator=(const Mat4& other) {
  for (int i = 0; i < 16; i++){
    m[i] = other.m[i];
  }
}

#endif
