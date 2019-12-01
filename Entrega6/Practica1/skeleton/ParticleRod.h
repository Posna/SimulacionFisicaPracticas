#pragma once
#include "ParticleLink.h"
class ParticleRod :
	public ParticleLink
{
public:
	/**
	* Holds the length of the rod.
	*/
	float length;
public:
	ParticleRod(Particle* a, Particle* b);
	/**
	* Fills the given contact structure with the contact needed
	* to keep the rod from extending or compressing.
	*/
	virtual unsigned addContact(ParticleContact* contact,
		unsigned limit) const;
};

