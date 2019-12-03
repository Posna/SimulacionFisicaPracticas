#include "Particle.h"

Particle::Particle(float radio, Vector4 c, Vector3 p, float age, bool cube): radio_(radio), color_(c), position_(p), age(age)
{
	t = new PxTransform(p);
	if(!cube)
		particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
	else
		particle_ = new RenderItem(CreateShape(PxBoxGeometry(radio, radio, radio)), t, c);
}

Particle::Particle(PxShape* part, Vector4 c, Vector3 p): color_(c), position_(p)
{
	t = new PxTransform(p);
	particle_ = new RenderItem(part, t, c);
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
	if (hasInfiniteMass()) return;
	// Update position
	position_ += velocity_*speed_* time;

	Vector3 totalAcc = Vector3(0);
	totalAcc += force_ * inverse_mass_;
	// Update linear velocity
	velocity_ += acceleration_* time;
	//Update linear velocity
	velocity_ += totalAcc * time;
	// Impose drag (damping)
	velocity_ *= powf(damping_, time);
	//Change the particles position
	*t = PxTransform(position_);
	clearForce();
}

void Particle::addForce(const Vector3& f)
{
	force_ += f;
}

Vector3 Particle::getVelocity() const
{
	return velocity_;
}

Vector3 Particle::getPos() const
{
	return position_;
}

float Particle::getAge() const
{
	return age;
}

float Particle::getMass() const
{
	return 1.0/inverse_mass_;
}

bool Particle::hasInfiniteMass()
{
	return inverse_mass_ <= 0.0f;
}

bool Particle::update(float t)
{
	integrate(t);
	age -= t;
	return (age < 0);
}

void Particle::clearForce()
{
	force_ = Vector3(0);
}
