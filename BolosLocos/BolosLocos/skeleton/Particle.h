#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

class Particle
{
public:
	Particle(float radio, Vector4 c = Vector4(0.5, 0.5, 0.5, 1), Vector3 p = Vector3(0.0f, 0.0f, 0.0f), float age = 1.0f, bool cube = false);
	Particle(PxShape* part, Vector4 c = Vector4(0.5, 0.5, 0.5, 1), Vector3 p = Vector3(0.0f, 0.0f, 0.0f));
	Particle(Vector4 c = Vector4(0.5, 0.5, 0.5, 1), Vector3 p = Vector3(0.0f, 0.0f, 0.0f));
	~Particle();

	void setShape(PxShape* part);
	void setVel(Vector3 v, float s);
	void setVel(Vector3 v) { velocity_ = v; }
	void setAcceleration(Vector3 a);
	void setDumping(float d);
	void setMass(float mass);
	void setGravity(float g) { g_ = g; }
	void setPos(Vector3 p) { position_ = p; }
	void setAge(float age) { age_ = age; }
	void integrate(float time);
	void addForce(const Vector3& f);
	bool hasInfiniteMass();

	Vector4 getColour() const { return colour_; }
	Vector3 getVelocity() const;
	Vector3 getPos() const;
	Vector3 getAcceleration() const { return acceleration_; }
	float getAge() const;
	float getMass() const;
	float getGravity() const { return g_; }
	float getRadio() const { return radio_; }
	float getInverseMass() const { return inverse_mass_; }

	virtual bool update(float t);
protected:
	RenderItem* particle_;
	PxTransform* t;

	void clearForce();


	Vector4 colour_;
	Vector3 position_;
	Vector3 velocity_ = Vector3(0, 0, 0);
	Vector3 acceleration_ = Vector3(0, 0, 0);
	Vector3 force_ = Vector3(0);

	float speed_ = 1.0f;
	float radio_;
	float damping_ = 0.999f;
	float inverse_mass_ = 1.0f / 0.1f;
	float age_;
	float g_ = 0;
};