#pragma once
#include "Particle.h"
class ParticleContactGenerator
{
public:
	virtual void updateContact(Particle* particle, float t) = 0;
private:
	float distanciaDosPuntos(const Vector3& a, const Vector3& b);
};

