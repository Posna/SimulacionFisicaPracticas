#pragma once
#include "ParticleForceGenerator.h"
class ParticleBuoyancy : public ParticleForceGenerator
{
	float maxDepth_;
	float volume_;
	// Considering a water plane parallel to XZ
	float waterHeight_;
	// Density of the liquid the object is submerged in
	float liquidDensity_;

public:
	ParticleBuoyancy(float maxDepth, float volume, float
		waterHeight,
		float liquidDensity = 1000.0f);
	virtual void updateForce(Particle* particle, float t);
	void addVolume(float volum) { volume_ += volum; }
	virtual ~ParticleBuoyancy();
};

