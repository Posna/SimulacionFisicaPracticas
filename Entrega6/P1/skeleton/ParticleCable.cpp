#include "ParticleCable.h"

ParticleCable::ParticleCable(Particle* a, Particle* b, float length): maxLength(length)
{
	particle[0] = a;
	particle[1] = b;
}

unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const
{
	// Find the length of the cable.
	float length = currentLength();
	// Check whether we’re overextended.
	if (length < maxLength)
	{
		return 0;
	}
	// Otherwise return the contact.
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];
	// Calculate the normal.
	Vector3 normal = particle[1]->getPos() - particle[0]
		->getPos();
	normal.normalize();
	contact->contactNormal = normal;
	contact->penetration = length - maxLength;
	contact->restitution = restitution;
	return 1;
}
