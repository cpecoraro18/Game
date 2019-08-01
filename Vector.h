#pragma once

#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

class Vector {
public:

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}


	Vector Add(const Vector& vec);
	Vector Subtract(const Vector& vec);
	Vector Multiply(const Vector& vec);
	Vector Divide(const Vector& vec);

	friend Vector& operator+(Vector& v1, const Vector& v2);
	friend Vector& operator-(Vector& v1, const Vector& v2);
	friend Vector& operator*(Vector& v1, const Vector& v2);
	friend Vector& operator/(Vector& v1, const Vector& v2);

	Vector& operator+=(const Vector& vec);
	Vector& operator-=(const Vector& vec);
	Vector& operator*=(const Vector& vec);
	Vector& operator/=(const Vector& vec);

	float dot(const Vector& lhs, const Vector& rhs);
	float cross(const Vector& lhs, const Vector& rhs);

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	
	float x, y;

};


#endif /* SRC_VECTOR_H_ */