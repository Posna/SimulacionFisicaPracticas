#pragma once
#include "Particle.h"
class ParticleContact
{
public:
	// Particles involved in the collision
	ParticleContact(Particle* a, Particle* b) {
		particle[0] = a;
		particle[1] = b;
	}
	void resolve(float t);
	float calculateSeparatingVelocity() const;
	Particle* particle[2];
	// Restitution coefficient
	float restitution = 0.5f;
	float penetration;
	// Contact normal,
	// from the first particle perspective
	Vector3 contactNormal;	// Resolves this contact for both velocity and interpenetration.
private:
	void resolveVelocity(float t);
	void resolveInterpenetration(float t);
};

