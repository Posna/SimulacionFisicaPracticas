#pragma once
#include "ParticleContact.h"
class ParticleCollisionRegistry
{
protected:

	typedef std::vector<Particle*> Registry;
	Registry registrations;
public:
	ParticleCollisionRegistry() {};
	
	void add(Particle* p);
	void remove(Particle* p);
	void clear();
	void updateCollisions(float t);
};

