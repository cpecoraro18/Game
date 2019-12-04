#include "AABB.h"
#include <algorithm>

AABB::AABB(float x, float y, float width, float height) {
	leftside = x;
	rightside = x + width;
	top = y;
	bottom = y + height;
	this->height = height;
	this->width = width;
}

void AABB::setDimentions(float x, float y) {
	leftside = x;
	rightside = x + width;
	top = y;
	bottom = y + height;
}

void AABB::setDimentions(float x, float y, float width, float height) {
	leftside = x;
	rightside = x + width;
	top = y;
	bottom = y + height;
	this->height = height;
	this->width = width;
}

AABB AABB::Union(AABB a, AABB b) {
	AABB c;
	c.leftside = std::min(a.leftside, b.leftside);
	c.rightside = std::max(a.rightside, b.rightside);
	c.top = std::min(a.top, b.top);
	c.bottom = std::max(a.bottom, b.bottom);
	return c;
}

float AABB::Area() {
	return(width * height);
}