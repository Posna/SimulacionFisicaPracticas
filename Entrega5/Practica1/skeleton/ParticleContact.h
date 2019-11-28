#pragma once
#include "Particle.h"
class ParticleContact
{
public:
	// Particles involved in the collision
	Particle* particle[2];
	// Restitution coefficient
	float restitution;
	float penetration;
	// Contact normal,
	// from the first particle perspective
	Vector3 contactNormal;protected:
	// Resolves this contact for both velocity and interpenetration.
	void resolve(float t);
	float calculateSeparatingVelocity() const;
private:
	void resolveVelocity(float t);
	void resolveInterpenetration(float t);
};

