#pragma once
#include "Particle.h"
class ParticleForceGenerator
{
public: 
	// Overload to provide functionality
	virtual void updateForce(Particle* particle, float t) = 0;
};

