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
	void addForce(const Vector3& f);
	bool hasInfiniteMass();

	Vector3 getVelocity() const;
	Vector3 getPos() const;
	float getAge() const;
	float getMass();
	
	bool update(float t);
private:
	void clearForce();

	RenderItem* particle_;
	PxTransform* t;

	Vector4 color_;
	Vector3 position_;
	Vector3 velocity_ = Vector3(0,0,0);
	Vector3 acceleration_ = Vector3(0, 0, 0);
	Vector3 force_ = Vector3(0);

	float speed_;
	float radio_;
	float damping_ = 0.999f;
	float inverse_mass_ = 1.0f/30.0f;
	float age;
};