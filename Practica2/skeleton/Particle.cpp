#include "Particle.h"

Particle::Particle(float radio, Vector4 c, Vector3 p): radio_(radio), color_(c), position_(p), PxRigidBody(RenderItem(CreateShape(PxSphereGeometry(radio)), new PxTransform(p), c), 1)
{
	PxTransform* t = new PxTransform(p);
	particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
	actor = new PxRigidBody(CreateShape(PxSphereGeometry(radio)), 1);
}

void Particle::setVel(Vector3 v, float s)
{
	velocity_ = v;
	speed_ = s;
}

void Particle::move()
{
	position_ += velocity_ * speed_;
	delete particle_;
	PxTransform* t = new PxTransform(position_);
	particle_ = new RenderItem(CreateShape(PxSphereGeometry(radio_)), t, color_);
}
