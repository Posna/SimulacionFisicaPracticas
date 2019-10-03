#include "Particle.h"

Particle::Particle(float radio, Vector4 c, Vector3 p, float age): radio_(radio), color_(c), position_(p), age_(age)
{
	t = new PxTransform(p);
	particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
}

Particle::~Particle()
{
	delete t;
	particle_->release();
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

void Particle::setDumping(float d)
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
	if (position_.y < 0.0f) {
		velocity_ = Vector3(velocity_.x, -velocity_.y/2.0f, velocity_.z);
	}
}

bool Particle::update(float t)
{
	integrate(t);
	age_ -= t;
	return (age_ < 0);
}