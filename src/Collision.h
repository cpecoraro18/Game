#pragma once
#ifndef SRC_COLLISION_H_
#define SRC_COLLISION_H_

#include "AABB.h"

#include <stack>


class Collision {
public:
	static bool checkAABB(const AABB& box1, const AABB& box2);


};


#endif /* SRC_COLLISION_H_ */