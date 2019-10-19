#pragma once

#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

class Vector {
public:

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}


	Vector& Add(Vector& vec);
	Vector& Subtract(Vector& vec);
	Vector& Multiply(Vector& vec);
	Vector& Divide(Vector& vec);

	friend Vector& operator+(Vector& v1, Vector& v2);
	friend Vector& operator-(Vector& v1, Vector& v2);
	friend Vector& operator*(Vector& v1, Vector& v2);
	friend Vector& operator/(Vector& v1, Vector& v2);

	Vector& operator+=(Vector& vec);
	Vector& operator-=(Vector& vec);
	Vector& operator*=(Vector& vec);
	Vector& operator/=(Vector& vec);

	float dot(Vector& lhs, Vector& rhs);
	float cross(Vector& lhs, Vector& rhs);

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	float x, y;

};


#endif /* SRC_VECTOR_H_ */
