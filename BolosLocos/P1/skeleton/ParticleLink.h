#pragma once
#include "ParticleContact.h"
#include "ParticleRigid.h"
class ParticleLink
{
public:
	//Holds the pair of particles that are connected by this link.
	ParticleRigid* particle[2];
protected:
	float currentLength() const;
public:
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
};

