#include "Particle.h"

Particle::Particle(int radio, float age, Vector4 c, Vector3 p): radio_(radio), color_(c), position_(p), age_(age)
{
	t = new PxTransform(p);
	particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
}

//Particle::Particle(float age, Vector3 p, Vector4 c): age(age), radio_(5), position_(p), color_(c)
//{
//	t = new PxTransform(p);
//	particle_ = new RenderItem(CreateShape(PxSphereGeometry(5)), t, c);
//	particle_->velocity = Vector3(0.0f, 0.0f, 0.0f);
//}

Particle::~Particle()
{
	delete t;
	if(particle_!= nullptr)
		particle_->release();
}

void Particle::setPos(Vector3 p)
{
	//t = new PxTransform(p);
	position_ = p;
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

bool Particle::update(float time)
{
	integrate(time);
	age_ -= time;
	return age_ < 0.0;
}

void Particle::free()
{
	particle_->release();
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