#include "MovementComponent.h"

MovementComponent::MovementComponent(float vx, float vy, float ax, float ay) {
	velocity = new Vector(vx, vy);
	acceleration = new Vector(ax, ay);

}

void MovementComponent::Update() {


}