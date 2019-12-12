#include "ParticleBuoyancy.h"

ParticleBuoyancy::ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity):
	maxDepth_(maxDepth), volume_(volume), waterHeight_(waterHeight), liquidDensity_(liquidDensity){

}

void ParticleBuoyancy::updateForce(Particle* particle, float t)
{
	float depth = particle->getPos().y;
	if (depth > (waterHeight_ + maxDepth_))
		// Out of the water -> nothing to do
		return;
	Vector3 f(0.0f, 0.0f, 0.0f);
	if (depth <= (waterHeight_ - maxDepth_))
	{ // Totally under the water
		f.y = liquidDensity_ * volume_;
	}
	else
	{
		float depthExterior = waterHeight_ + maxDepth_;
		float volumeFactor = (depth - depthExterior) / (2 * maxDepth_);
		f.y = liquidDensity_ * volumeFactor * volume_;
	}
	particle->addForce(f);
}

void ParticleBuoyancy::updateForce(ParticleRigid* particle, float t)
{
	float depth = particle->getPosition().y;
	if (depth > (waterHeight_ + maxDepth_))
		// Out of the water -> nothing to do
		return;
	Vector3 f(0.0f, 0.0f, 0.0f);
	if (depth <= (waterHeight_ - maxDepth_))
	{ // Totally under the water
		f.y = liquidDensity_ * volume_;
	}
	else
	{
		float depthExterior = waterHeight_ + maxDepth_;
		float volumeFactor = (depth - depthExterior) / (2 * maxDepth_);
		f.y = liquidDensity_ * volumeFactor * volume_;
	}
	particle->addForce(f, 1);
}

ParticleBuoyancy::~ParticleBuoyancy()
{

}
