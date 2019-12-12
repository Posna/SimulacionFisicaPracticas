#include "ParticleAnchoredSpring.h"


ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor, float k, float restLength) : anchor_(anchor), k_(k),
restLength_(restLength)
{

}

void ParticleAnchoredSpring::updateForce(Particle* particle, float t)
{
	Vector3 f = particle->getPos();
	f -= *anchor_;
	// Length
	float length = f.normalize();
	// Resulting force
	f = -((length - restLength_) * k_)*f;
	particle->addForce(f);
}

ParticleAnchoredSpring::~ParticleAnchoredSpring()
{

}
