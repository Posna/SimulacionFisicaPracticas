#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

class Particle: public PxRigidBody 
{
public:
	Particle(float radio, Vector4 c = Vector4(0.5, 0.5, 0.5, 1), Vector3 p = Vector3(0.0f, 0.0f, 0.0f));
	void setVel(Vector3 v, float s);
	void move();
private:
	RenderItem* particle_;
	PxRigidBody* actor;
	Vector4 color_;
	Vector3 position_;
	Vector3 velocity_;
	Vector3 aceleration_;
	float speed_;
	float radio_;
};