#pragma once
#include "Particle.h"
#include "ParticleRigid.h"
class ParticleContact
{
public:
	// Particles involved in the collision
	ParticleContact(ParticleRigid* a, ParticleRigid* b) {
		particle[0] = a;
		particle[1] = b;
	}
	void resolve(float t);
	float calculateSeparatingVelocity() const;
	ParticleRigid* particle[2];
	// Restitution coefficient
	float restitution = 0.5f;
	float penetration;
	// Contact normal,
	// from the first particle perspective
	Vector3 contactNormal;
private:
	void resolveVelocity(float t);
	void resolveInterpenetration(float t);
};
