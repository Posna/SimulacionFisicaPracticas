#pragma once
#include "ParticleContact.h"
#include "ParticleLink.h"
class ParticleCable: public ParticleLink
{
public:
	/**
	* Holds the maximum length of the cable.
	*/
	float maxLength;
	/**
	* Holds the restitution (bounciness) of the cable.
	*/
	float restitution = 0.5f;
public:
	ParticleCable(ParticleRigid* a, ParticleRigid* b, float length);
	/**
	* Fills the given contact structure with the contact needed
	* to keep the cable from overextending.
	*/
	virtual unsigned addContact(ParticleContact* contact,
		unsigned limit) const;

};

