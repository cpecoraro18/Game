#pragma once
#ifndef SRC_MOVEMENTCOMPONENT_H_
#define SRC_MOVEMENTCOMPONENT_H_

#include "Component.h"
#include "Vector.h"

class MovementComponent : public Component {
public:
	MovementComponent(float vx = 0, float vy = 0, float ax = 0, float ay = 0);

	void Update();

	Vector* velocity;
	Vector* acceleration;
private:
	
};

#endif /* SRC_MOVEMENTCOMPONENT_H_ */