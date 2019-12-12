#pragma once
#include "ParticleContact.h"
class ParticleCollisionRegistry
{
protected:

	typedef std::vector<ParticleRigid*> Registry;
	Registry registrations;
public:
	ParticleCollisionRegistry() {};
	
	void add(ParticleRigid* p);
	void remove(ParticleRigid* p);
	void clear();
	void updateCollisions(float t);
};

