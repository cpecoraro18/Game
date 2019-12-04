#pragma once
#ifndef SRC_AABB_H_
#define SRC_AABB_H_

class AABB {
public:
	AABB(float x, float y, float width, float height);
	AABB() {}

	void setDimentions(float x, float y);
	void setDimentions(float x, float y, float width, float height);
	AABB Union(AABB a, AABB b);
	float Area();


	float rightside;
	float leftside;
	float bottom;
	float top;
	float width;
	float height;
};

#endif /* SRC_AABB_H_ */