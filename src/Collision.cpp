#include "Collision.h"
#include <iostream>

bool Collision::checkAABB(const AABB& box1, const AABB& box2) {

	if (box1.leftside < box2.rightside &&
		box1.rightside > box2.leftside &&
		box1.top < box2.bottom &&
		box1.bottom > box2.top) {
		return true;
	}

	return false;
}
