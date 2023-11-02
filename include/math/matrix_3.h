//--------------------------------------------------------------//
//  Math Library
//  Matrix 3 Class Definition.
//--------------------------------------------------------------//
//
//   m0 m1 m2
//   m3 m4 m5
//   m6 m7 m8
//
//--------------------------------------------------------------//
#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "math/vector_2.h"
#include "math/vector_3.h"

class Mat3 {
public:

	Mat3();
	Mat3(float *values_array);
	Mat3(float value);
	Mat3(Vec3 a, Vec3 b, Vec3 c);

	Mat3(const Mat3& copy);
	~Mat3();

	static Mat3 Identity();

	Mat3 Multiply(const Mat3& other) const;

	float Determinant() const;

	Mat3 Adjoint() const;
	bool GetInverse(Mat3& out) const;
	bool Inverse();

	Mat3 Transpose() const;

	static Mat3 Translate(const Vec2& position);
	static Mat3 Translate(float x, float y);

	Vec3 GetColum(int colum) const;
	Vec3 GetLine(int line) const;

	inline Mat3 operator+(const Mat3& other) const;
	inline Mat3& operator+=(const Mat3& other);
	inline Mat3 operator+(float value) const;
	inline Mat3& operator+=(float value);
	inline Mat3 operator-(const Mat3& other) const;
	inline Mat3& operator-=(const Mat3& other);
	inline Mat3 operator-(float value) const;
	inline Mat3& operator-=(float value);
	inline Mat3 operator*(float value) const;
	inline Mat3& operator*=(float value);
	inline Mat3 operator/(float value) const;
	inline Mat3& operator/=(float value);
	bool operator==(const Mat3& other) const;
	bool operator!=(const Mat3& other) const;
	inline void operator=(const Mat3& other);

	float m[9];
};


inline Mat3 Mat3::operator+(const Mat3& other) const {
  Mat3 res;
  for (int i = 0; i < 9; i++){
    res.m[i] = m[i] + other.m[i];
  }
	return res;
}

inline Mat3& Mat3::operator+=(const Mat3& other) {
  for (int i = 0; i < 9; i++){
    m[i] += other.m[i];
  }
	return *this;
}

inline Mat3 Mat3::operator+(float value) const {
	Mat3 res;
  for (int i = 0; i < 9; i++){
    res.m[i] = m[i] + value;
  }
	return res;
}

inline Mat3& Mat3::operator+=(float value) {
  for (int i = 0; i < 9; i++){
    m[i] += value;
  }
	return *this;
}

inline Mat3 Mat3::operator-(const Mat3& other) const {
  Mat3 res;
  for (int i = 0; i < 9; i++){
    res.m[i] = m[i] - other.m[i];
  }
	return res;

}

inline Mat3& Mat3::operator-=(const Mat3& other) {
	for (int i = 0; i < 9; i++){
    m[i] -= other.m[i];
  }
	return *this;
}

inline Mat3 Mat3::operator-(float value) const {
	Mat3 res;
  for (int i = 0; i < 9; i++){
    res.m[i] = m[i] - value;
  }
	return res;
}

inline Mat3& Mat3::operator-=(float value) {
	for (int i = 0; i < 9; i++){
    m[i] -= value;
  }
	return *this;
}

inline Mat3 Mat3::operator*(float value) const {
	Mat3 res;
  for (int i = 0; i < 9; i++){
    res.m[i] = m[i] * value;
  }
	return res;
}

inline Mat3& Mat3::operator*=(float value) {
	for (int i = 0; i < 9; i++){
    m[i] *= value;
  }
	return *this;
}

inline Mat3 Mat3::operator/(float value) const {
	Mat3 res;
  for (int i = 0; i < 9; i++){
    res.m[i] = m[i] / value;
  }
	return res;
}

inline Mat3& Mat3::operator/=(float value) {
	for (int i = 0; i < 9; i++){
    m[i] /= value;
  }
	return *this;
}

inline bool Mat3::operator==(const Mat3& other) const {
	for (int i = 0; i < 9; i++){
    if(m[i] != other.m[i]) return false;
  }
	return true;
}

inline bool Mat3::operator!=(const Mat3& other) const {
	for (int i = 0; i < 9; i++){
    if(m[i] != other.m[i]) return true;
  }
	return false;
}

inline void Mat3::operator=(const Mat3& other) {
  for (int i = 0; i < 9; i++){
    m[i] = other.m[i];
  }
}

inline Mat3 Mat3::Identity() {
	return Mat3(Vec3(1,0,0),Vec3(0,1,0), Vec3(0,0,1));
}

inline float Mat3::Determinant() const {
	return (m[0] * m[4] * m[8]) + (m[1] * m[5] * m[6]) + (m[2] * m[3] * m[7])
  - (m[2] * m[4] * m[6]) - (m[1] * m[3] * m[8]) - (m[0] * m[5] * m[7]);
}

inline bool Mat3::GetInverse(Mat3& out) const {
  float det = this->Determinant();
  if(det == 0) return false;
  out = this->Adjoint() / det;
	return true;
}

inline bool Mat3::Inverse() {	
  float det = this->Determinant();
  if(det == 0) return false;
  operator= (this->Adjoint().Transpose() / det);
	return true;
}

inline Mat3 Mat3::Translate(const Vec2& mov_vector) {	
  Mat3 res = Mat3::Identity();
  res.m[2] = mov_vector.x;
  res.m[5] = mov_vector.y;
	return res;
}

inline Mat3 Mat3::Translate(float x, float y) {
	Mat3 res = Mat3::Identity();
  res.m[2] = x;
  res.m[5] = y;
	return res;
}

inline Mat3 Mat3::Multiply(const Mat3& other) const {
  Mat3 res;
  for (int row = 0; row < 3; row++){
    for(int col = 0; col<3; col++){
      res.m[row*3 + col] = 
        m[row*3 + 0] * other.m[0*3 + col] + 
        m[row*3 + 1] * other.m[1*3 + col] + 
        m[row*3 + 2] * other.m[2*3 + col];
    }
  }
	return res;
}

inline Mat3 Mat3::Adjoint() const {

	return Mat3(
    Vec3(m[4]*m[8] - m[5]*m[7], -(m[3]*m[8] - m[5]*m[6]), m[3]*m[7] - m[4]*m[6]),
    Vec3(-(m[1]*m[8] - m[2]*m[7]), m[0]*m[8] - m[2]*m[6], -(m[0]*m[7] - m[1]*m[6])),
    Vec3(m[1]*m[5] - m[2]*m[4], -(m[0]*m[5] - m[2]*m[3]), m[0]*m[4] - m[1]*m[3])
  );
}

inline Mat3 Mat3::Transpose() const {
  return Mat3(
    Vec3(m[0], m[3], m[6]), 
    Vec3(m[1], m[4], m[7]), 
    Vec3(m[2], m[5], m[8])
  );
}

inline Vec3 Mat3::GetColum(int colum) const {
	return Vec3(m[colum], m[3 + colum], m[6 + colum]);
}

inline Vec3 Mat3::GetLine(int line) const {
	return Vec3(m[line*3 + 0], m[line*3 + 1], m[line*3 + 2]);
}

#endif 