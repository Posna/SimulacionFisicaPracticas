#pragma once
#include "ParticleForceGenerator.h"
class ParticleWind: public ParticleForceGenerator
{
	// Acceleration for gravity
	Vector3 g;
public:
	ParticleWind(const Vector3& gravity) : g(gravity) {}
	virtual void updateForce(Particle* particle, float t);
};

