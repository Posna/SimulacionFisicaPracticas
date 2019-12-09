#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(ParticleRigid* particle, ParticleForceGenerator* fg)
{
	registrations.push_back({particle, fg});
}

void ParticleForceRegistry::remove(ParticleRigid* particle, ParticleForceGenerator* fg)
{
	int i = 0;
	while (i < registrations.size() && (registrations[i].particle != particle || registrations[i].fg != fg)) { i++; }
	if (i < registrations.size()) {
		registrations.erase(registrations.begin() + i);
	}
}

void ParticleForceRegistry::clear()
{
	registrations.clear();
}

void ParticleForceRegistry::updateForces(float t)
{
	for (ParticleForceRegistration p : registrations) {
		p.fg->updateForce(p.particle, t);
		if (p.fg->isInstant()) {
			remove(p.particle, p.fg);
		}
	}
}
