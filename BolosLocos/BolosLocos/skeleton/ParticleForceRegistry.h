#pragma once
#include "ParticleForceGenerator.h"
class ParticleForceRegistry 
{
protected:
	// Storage for generator-particle entry
	struct ParticleForceRegistration
	{
		//ParticleForceRegistration(Particle* p, ParticleForceGenerator* f): particle(p), fg(f) {}
		ParticleRigid* particle;
		ParticleForceGenerator* fg;
	};
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;
public:
	ParticleForceRegistry() {};
	//Associate generator with a particle
	void add(ParticleRigid* particle, ParticleForceGenerator* fg);
	// Remove association
	void remove(ParticleRigid* particle, ParticleForceGenerator* fg);
	// Removes all associations. Particle and Generators won't be deleted
	void clear();
	// Update all the generators in the registry
	void updateForces(float t);

};

