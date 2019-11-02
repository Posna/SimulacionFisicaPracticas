#pragma once
#include "ParticleForceGenerator.h"
class ParticleAnchoredSpring: public ParticleForceGenerator
{
	Vector3 anchor_;

	//Elasticity const
	float k_;

	float restLength_;
public:
	ParticleAnchoredSpring(Vector3 anchor, float k, float restLength);
	virtual void updateForce(Particle* particle, float t);
	virtual ~ParticleAnchoredSpring();
};

