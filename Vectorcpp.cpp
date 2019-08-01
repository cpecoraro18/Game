#include "Vector.h"


Vector Vector::Add(const Vector& vec) {
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector Vector::Subtract(const Vector& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector Vector::Multiply(const Vector& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector Vector::Divide(const Vector& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vector& operator+(Vector& v1, const Vector& v2) {
	return v1.Add(v2);

}
Vector& operator-(Vector& v1, const Vector& v2) {
	return v1.Subtract(v2);
}
Vector& operator*(Vector& v1, const Vector& v2) {
	return v1.Multiply(v2);
}
Vector& operator/(Vector& v1, const Vector& v2) {
	return v1.Divide(v2);
}

Vector& Vector::operator+=(const Vector& vec) {
	return this->Add(vec);
}
Vector& Vector::operator-=(const Vector& vec) {
	return this->Subtract(vec);
}
Vector& Vector::operator*=(const Vector& vec) {
	return this->Multiply(vec);
}
Vector& Vector::operator/=(const Vector& vec) {
	return this->Divide(vec);
}

float Vector::dot(const Vector& lhs, const Vector& rhs) {
	return(lhs.x*rhs.x + lhs.y*rhs.y);
	
}

float Vector::cross(const Vector& lhs, const Vector& rhs) {
	return lhs.x * rhs.y - lhs.y * rhs.x;
}