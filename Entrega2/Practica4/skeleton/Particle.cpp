#include "Particle.h"

Particle::Particle(float radio, Vector4 c, Vector3 p): radio_(radio), color_(c), position_(p)
{
	t = new PxTransform(p);
	particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
}

Particle::~Particle()
{
	delete t;
	particle_->release();
}

void Particle::setPos(Vector3 p)
{
	t = new PxTransform(p);
}

Vector3 Particle::getPos() const
{
	return position_;
}

void Particle::setVel(Vector3 v, float s)
{
	velocity_ = v;
	speed_ = s;
}

Vector3 Particle::getVel() const
{
	return velocity_;
}

void Particle::setAcceleration(Vector3 a)
{
	acceleration_ = a;
}

void Particle::setDamping(float d)
{
	damping_ = d;
}

void Particle::setMass(float mass)
{
	inverse_mass_ = 1.0 / mass;
}

void Particle::integrate(float time)
{
	// Trivial case, infinite mass --> do nothing
	if (inverse_mass_ <= 0.0f) return;
	// Update position
	position_ += velocity_*speed_* time;
	// Update linear velocity
	velocity_ += acceleration_* time;
	// Impose drag (damping)
	velocity_ *= powf(damping_, time);
	//Change the particles position
	*t = PxTransform(position_);
}