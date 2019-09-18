#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

class Particle
{
public:
	Particle(float radio, Vector4 c = Vector4(0.5, 0.5, 0.5, 1), Vector3 p = Vector3(0.0f, 0.0f, 0.0f));
	void setVel(Vector3 v, float s);
	void integrate(float time);
private:
	RenderItem* particle_;
	PxTransform* t;
	Vector4 color_;
	Vector3 position_;
	Vector3 velocity_ = Vector3(0,0,0);
	float speed_;
	float radio_;
	float inverse_mass_ = 1.0f/30.0f;
};