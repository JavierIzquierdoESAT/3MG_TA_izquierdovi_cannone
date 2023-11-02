#include "math/vector_3.h"

const Vec3 Vec3::up = Vec3(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::down = Vec3(0.0f, -1.0f, 0.0f);
const Vec3 Vec3::right = Vec3(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::left = Vec3(-1.0f, 0.0f, 0.0f);
const Vec3 Vec3::forward = Vec3(0.0f, 0.0f, 1.0f);
const Vec3 Vec3::back = Vec3(0.0f, 0.0f, -1.0f);
const Vec3 Vec3::zero = Vec3(0.0f, 0.0f, 0.0f);
const Vec3 Vec3::unit = Vec3(1.0f, 1.0f, 1.0f);

Vec3::Vec3() {
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

Vec3::Vec3(float a) {
	x = a;
	y = a;
	z = a;
}

Vec3::Vec3(const Vec3& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

//Author: Alan Gutierrez Ramirez
Vec3::Vec3(float* values_array)
{
	for(int i=0; i<3; ++i)
	{
		x = (*(values_array));
		y = (*(values_array + 1));
		z = (*(values_array + 2));
	}
}

Vec3::~Vec3() {}
