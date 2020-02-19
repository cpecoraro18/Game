#include "PhysicsComponent.h"
#include "Collision.h"

PhysicsComponent::PhysicsComponent(float x, float y, float w, float h, int xb, int yb, int wb, int hb) : 
	hitboxXBuffer(xb), hitboxYBuffer(yb), hitboxWBuffer(wb), hitboxHBuffer(hb) {

	hitbox = new AABB(x + hitboxXBuffer, y + hitboxYBuffer, w + hitboxWBuffer, h + hitboxHBuffer);


}

void PhysicsComponent::Update() {


}

void PhysicsComponent::setHitboxDimentions(int x, int y, int w, int h) {
	hitbox->setDimentions(x + hitboxXBuffer, y + hitboxYBuffer, w + hitboxWBuffer, h + hitboxHBuffer);

}