#pragma once
#include "ParticleForceGenerator.h"
class ParticleGravity :public ParticleForceGenerator
{
	// Acceleration for gravity
	Vector3 g;
public:
	ParticleGravity(const Vector3& gravity) : g(gravity) {}
	virtual void updateForce(Particle* particle, float t);
};

void ParticleGravity::updateForce(Particle* particle, float t)
{
	if (!particle->hasInfiniteMass()) return;
	particle->addForce(g * particle->getMass());
}