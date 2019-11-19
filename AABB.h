#pragma once
#ifndef SRC_AABB_H_
#define SRC_AABB_H_

class AABB {
public:
	AABB(float x, float y, float width, float height);

	void setDimentions(float x, float y);

	void setDimentions(float x, float y, float width, float height);

	float rightside;
	float leftside;
	float bottom;
	float top;
	float width;
	float height;
};

#endif /* SRC_AABB_H_ */