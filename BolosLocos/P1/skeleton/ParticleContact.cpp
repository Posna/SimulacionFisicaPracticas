#include "ParticleContact.h"

void ParticleContact::resolve(float t)
{
	//if ((particle[0]->getPos() - particle[1]->getPos()).magnitude() < particle[0]->getRadio() + particle[1]->getRadio()) {
		//penetration = particle[0]->getRadio() + particle[1]->getRadio() - (particle[1]->getPos() - particle[0]->getPos()).magnitude();
		//contactNormal = particle[0]->getPos() - particle[1]->getPos();
		//contactNormal.normalize();
		resolveVelocity(t);
		resolveInterpenetration(t);
	//}
}

float ParticleContact::calculateSeparatingVelocity() const
{
	Vector3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1])
		relativeVelocity -= particle[1]->getVelocity();
	return relativeVelocity.dot(contactNormal);

}

void ParticleContact::resolveVelocity(float t)
{
	// Find the velocity in the direction of the contact.
	float separatingVelocity = calculateSeparatingVelocity();
	// Check whether it needs to be resolved.
	if (separatingVelocity > 0)
	{
		// The contact is either separating or stationary - there’s
		// no impulse required.
		return;
	}
	// Calculate the new separating velocity.
	float newSepVelocity = -separatingVelocity * restitution;
	float deltaVelocity = newSepVelocity - separatingVelocity;
	// We apply the change in velocity to each object in proportion to
	// its inverse mass (i.e., those with lower inverse mass [higher
	// actual mass] get less change in velocity).
	float totalInverseMass = particle[0]->particle_->getInvMass();
	if (particle[1]) totalInverseMass += particle[1]->particle_->getInvMass();
	// If all particles have infinite mass, then impulses have no effect.
	if (totalInverseMass <= 0) return;
	// Calculate the impulse to apply.
	float impulse = deltaVelocity / totalInverseMass;
	// Find the amount of impulse per unit of inverse mass.
	Vector3 impulsePerIMass = contactNormal * impulse;
	// Apply impulses: they are applied in the direction of the contact,
// and are proportional to the inverse mass.
	particle[0]->particle_->setLinearVelocity(particle[0]->particle_->getLinearVelocity() +
		impulsePerIMass * particle[0]->particle_->getInvMass());
	if (particle[1])
	{
		// Particle 1 goes in the opposite direction.
		particle[1]->particle_->setLinearVelocity(particle[1]->particle_->getLinearVelocity() +
			impulsePerIMass * -particle[1]->getInverseMass()
		);
	}
	
	
	//// Find the velocity in the direction of the contact.
	//float separatingVelocity = calculateSeparatingVelocity();
	//// Check whether it needs to be resolved.
	//if (separatingVelocity > 0)
	//{
	//	// The contact is either separating or stationary - there’s
	//	// no impulse required.
	//	return;
	//}
	//// Calculate the new separating velocity.
	//float newSepVelocity = -separatingVelocity * restitution;
	//// Check the velocity build-up due to acceleration only.
	//Vector3 accCausedVelocity = particle[0]->getAcceleration();
	//if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();
	//float accCausedSepVelocity = (accCausedVelocity.x * contactNormal.x + accCausedVelocity.y * contactNormal.y + accCausedVelocity.z * contactNormal.z) * t;
	//// If we’ve got a closing velocity due to acceleration build-up,
	//// remove it from the new separating velocity.
	//if (accCausedSepVelocity < 0)
	//{
	//	newSepVelocity += restitution * accCausedSepVelocity;
	//	// Make sure we haven’t removed more than was
	//	// there to remove.
	//	if (newSepVelocity < 0) newSepVelocity = 0;
	//}
	//float deltaVelocity = newSepVelocity - separatingVelocity;
	//// We apply the change in velocity to each object in proportion to
	//// its inverse mass (i.e., those with lower inverse mass [higher
	//// actual mass] get less change in velocity).
	//float totalInverseMass = particle[0]->getInverseMass();
	//if (particle[1]) totalInverseMass += particle[1]->getInverseMass();
	//// If all particles have infinite mass, then impulses have no effect.
	//if (totalInverseMass <= 0) return;
	//// Calculate the impulse to apply.
	//float impulse = deltaVelocity / totalInverseMass;
	//// Find the amount of impulse per unit of inverse mass.
	//Vector3 impulsePerIMass = contactNormal * impulse;
	////Vector3 impulsePerIMass1 = -1*contactNormal * impulse;
	//// Apply impulses: they are applied in the direction of the contact,
	//// and are proportional to the inverse mass.
	//particle[0]->setVel(particle[0]->getVelocity() +
	//	impulsePerIMass * particle[0]->getInverseMass()
	//);
	//if (particle[1]) {
	//	// Particle 1 goes in the opposite direction.
	//	particle[1]->setVel(particle[1]->getVelocity() +
	//		impulsePerIMass * -particle[1]->getInverseMass()
	//	);
	//}
}

void ParticleContact::resolveInterpenetration(float t)
{

	// If we don’t have any penetration, skip this step.
	if (penetration <= 0) return;
	// The movement of each object is based on its inverse mass, so
	// total that.
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();
	// If all particles have infinite mass, then we do nothing.
	if (totalInverseMass <= 0) return;
	// Find the amount of penetration resolution per unit of inverse mass.
	Vector3 movePerIMass = contactNormal *
		(-penetration / totalInverseMass);
	// Apply the penetration resolution.
	particle[0]->setPos(particle[0]->getPos() +
		movePerIMass * -particle[0]->getInverseMass());
	if (particle[1])
	{
		particle[1]->setPos(particle[1]->getPos() +
			movePerIMass * particle[1]->getInverseMass());
	}
}
