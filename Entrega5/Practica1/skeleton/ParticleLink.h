#pragma once
#include "ParticleContactGenerator.h"
class ParticleLink: public ParticleContactGenerator
{
public:
	//Holds the pair of particles that are connected by this link.
	Particle* particle[2];
protected:
	float currentLength() const;
public:
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
};

