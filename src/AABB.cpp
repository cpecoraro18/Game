#include "AABB.h"

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
