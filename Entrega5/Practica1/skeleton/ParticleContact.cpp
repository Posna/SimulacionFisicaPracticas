#include "ParticleContact.h"

void ParticleContact::resolve(float t)
{
	resolveVelocity(t);
	resolveInterpenetration(t);
}

float ParticleContact::calculateSeparatingVelocity() const
{
	Vector3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1])
		relativeVelocity -= particle[1]->getVelocity();
	return relativeVelocity.x * contactNormal.x + relativeVelocity.y * contactNormal.y + relativeVelocity.z * contactNormal.z;
}

void ParticleContact::resolveVelocity(float t)
{
	//Get current separating velocity
	float separatingVel = calculateSeparatingVelocity();

	if (separatingVel > 0)
		return;
	float newSepVelocity = -separatingVel * restitution;
	Vector3 accCausedVelocity = particle[0]->getAcceleration();
	float accCausedVelocity = accCausedVelocity * contactNormal * t;
	Vector3 v1 = particle[0]->getVelocity();
	Vector3 v2 = particle[1]->getVelocity();

	Vector3 normal = particle[0]->getPos() - particle[1]->getPos();

	//Cumpute separating velocity after collision
	Vector3 v1N = v2 * (1.0 / particle[0]->getMass()) * particle[0]->Particle::getGravity();
	Vector3 v2N = v1 * (1.0 / particle[1]->getMass()) * particle[1]->Particle::getGravity();

	//Compute total impulse

}
