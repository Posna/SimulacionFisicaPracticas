#include "Particle.h"

Particle::Particle(float radio, Vector4 c, Vector3 p): radio_(radio), color_(c), position_(p)
{
	t = new PxTransform(p);
	particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
}

void Particle::setVel(Vector3 v, float s)
{
	velocity_ = v;
	speed_ = s;
}

void Particle::setAcceleration(Vector3 a)
{
	acceleration_ = a;
}

void Particle::integrate(float time)
{
	// Trivial case, infinite mass --> do nothing
	if (inverse_mass_ <= 0.0f) return;
	// Update position
	position_ += velocity_* time;
	// Update linear velocity
	velocity_ += acceleration_* time;
	// Impose drag (damping)
	velocity_ *= powf(damping_, time);
	//Change the particles position
	*t = PxTransform(position_);
}
