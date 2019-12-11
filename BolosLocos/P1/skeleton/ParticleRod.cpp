//#include "ParticleRod.h"
//
//ParticleRod::ParticleRod(Particle* a, Particle* b)
//{
//	length = (a->getPos() - b->getPos()).magnitude();
//	particle[0] = a;
//	particle[1] = b;
//}
//
//unsigned ParticleRod::addContact(ParticleContact* contact, unsigned limit) const
//{
//	// Find the length of the rod.
//	float currentLen = currentLength();
//	// Check whether we�re overextended.
//	if (currentLen == length)
//	{
//		return 0;
//	}
//	// Otherwise return the contact.
//	contact->particle[0] = particle[0];
//	contact->particle[1] = particle[1];
//	// Calculate the normal.
//	Vector3 normal = particle[1]->getPos() - particle[0]
//		->getPos();
//	normal.normalize();
//	// The contact normal depends on whether we�re extending
//	// or compressing.
//	if (currentLen > length) {
//		contact->contactNormal = normal;
//		contact->penetration = currentLen - length;
//	}
//	else {
//		contact->contactNormal = normal * -1;
//		contact->penetration = length - currentLen;
//	}
//	// Always use zero restitution (no bounciness).
//	contact->restitution = 0;
//	return 1;
//}
