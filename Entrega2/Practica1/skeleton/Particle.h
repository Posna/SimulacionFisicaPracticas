#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

class Particle
{
public:
	Particle(float radio, Vector4 c = Vector4(0.5, 0.5, 0.5, 1), Vector3 p = Vector3(0.0f, 0.0f, 0.0f), float age = 1.0f);
	~Particle();
	void setVel(Vector3 v, float s);
	void setAcceleration(Vector3 a);
	void setDumping(float d);
	void setMass(float mass);
	void integrate(float time);
	bool update(float t);
protected:
	Vector3 position_;
	Vector4 color_;
	Vector3 velocity_ = Vector3(0,0,0);
	Vector3 acceleration_ = Vector3(0, 0, 0);
private:
	RenderItem* particle_;
	PxTransform* t;
	float speed_;
	float radio_;
	float damping_ = 0.999f;
	float inverse_mass_ = 1.0f/30.0f;
	float age_;
	bool puedeRebote;
};