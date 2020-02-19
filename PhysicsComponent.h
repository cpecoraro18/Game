#pragma once
#ifndef SRC_PHYSICCOMPONENT_H_
#define SRC_PHYSICSCOMPONENT_H_

#include "Component.h"
#include "AABB.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent(float x, float y, float w, float h, int xb, int yb, int wb, int hb);

	void Update();

	void setHitboxDimentions(int x, int y, int w, int h);
	AABB* hitbox;

private:
	int hitboxXBuffer;
	int hitboxYBuffer;
	int hitboxWBuffer;
	int hitboxHBuffer;
};

#endif /* SRC_PHYSICSCOMPONENT_H_ */