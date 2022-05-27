#include "Vec2.hpp"

Vec2::Vec2() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2& Vec2::Add(const Vec2& vec) {
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vec2& Vec2::Subtract(const Vec2& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vec2& Vec2::Multiply(const Vec2& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vec2& Vec2::Divide(const Vec2& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vec2& operator+(Vec2& v1, const Vec2& v2) {
	return v1.Add(v2);
}

Vec2& operator-(Vec2& v1, const Vec2& v2) {
	return v1.Subtract(v2);
}

Vec2& operator*(Vec2& v1, const Vec2& v2) {
	return v1.Multiply(v2);
}

Vec2& operator/(Vec2& v1, const Vec2& v2) {
	return v1.Divide(v2);
}

Vec2& operator*(const int& i, const Vec2& vec) {
	return i * vec;
}

Vec2& Vec2::operator+=(const Vec2& vec) {
	return this->Add(vec);
}

Vec2& Vec2::operator-=(const Vec2& vec) {
	return this->Subtract(vec);
}

Vec2& Vec2::operator*=(const Vec2& vec) {
	return this->Multiply(vec);
}

Vec2& Vec2::operator/=(const Vec2& vec) {
	return this->Divide(vec);
}

Vec2& Vec2::operator*(const int& i) {
	this->x *= i;
	this->y *= i;

	return *this;
}

Vec2& Vec2::Zero() {
	this->x = 0;
	this->y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vec) {
	stream << "Vec2D(" << vec.x << "," << vec.y << ")";
	return stream;
}
