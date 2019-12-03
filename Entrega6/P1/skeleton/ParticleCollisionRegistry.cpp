#include "ParticleCollisionRegistry.h"

void ParticleCollisionRegistry::add(Particle* p)
{
	registrations.push_back(p);
}

void ParticleCollisionRegistry::remove(Particle* p)
{
	int i = 0;
	while (i < registrations.size() && registrations[i] != p) { i++; }
	if (i < registrations.size()) {
		registrations.erase(registrations.begin() + i);
	}
}

void ParticleCollisionRegistry::clear()
{
	registrations.clear();
}

void ParticleCollisionRegistry::updateCollisions(float t)
{
	for (auto a = registrations.begin(); a != registrations.end(); a++) {
		for (auto b = a+1; b != registrations.end(); b++) {
			ParticleContact p = ParticleContact(*a, *b);
			p.resolve(t);
		}
	}
}
