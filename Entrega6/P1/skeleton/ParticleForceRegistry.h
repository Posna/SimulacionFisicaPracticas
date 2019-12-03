#pragma once
#include "ParticleForceGenerator.h"
class ParticleForceRegistry 
{
protected:
	// Storage for generator-particle entry
	struct ParticleForceRegistration
	{
		//ParticleForceRegistration(Particle* p, ParticleForceGenerator* f): particle(p), fg(f) {}
		Particle* particle;
		ParticleForceGenerator* fg;
	};
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;
public:
	ParticleForceRegistry() {};
	//Associate generator with a particle
	void add(Particle* particle, ParticleForceGenerator* fg);
	// Remove association
	void remove(Particle* particle, ParticleForceGenerator* fg);
	// Removes all associations. Particle and Generators won't be deleted
	void clear();
	// Update all the generators in the registry
	void updateForces(float t);

};

