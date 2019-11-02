#include "ParticleSpring.h"


ParticleSpring::ParticleSpring(Particle * other, float k, float restLeangth)
{
	
}

void ParticleSpring::updateForce(Particle * particle, float t)
{
	// Calculate distance vector
	Vector3 f = particle->getPos();
	f -= other_->getPos();
	// Length
	float length = f.normalize();
	// Resulting force
	float deltaL = length - restLength_;
	float forceMagnitude = -k_ * deltaL;
	f *= forceMagnitude;
	particle->addForce(f);
}

ParticleSpring::~ParticleSpring()
{
}
