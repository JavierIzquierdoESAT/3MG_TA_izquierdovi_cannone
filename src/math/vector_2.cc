#include "math/vector_2.h"

const Vec2 Vec2::down = Vec2(0.0f, -1.0f);
const Vec2 Vec2::left = Vec2(-1.0f, 0.0f);
const Vec2 Vec2::one = Vec2(1.0f, 1.0f);
const Vec2 Vec2::right = Vec2(1.0f, 0.0f);
const Vec2 Vec2::up = Vec2(0.0f, 1.0f);
const Vec2 Vec2::zero = Vec2(0.0f, 0.0f);

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2::Vec2(const Vec2& other) {
	x = other.x;
	y = other.y;
}

Vec2::~Vec2() {}