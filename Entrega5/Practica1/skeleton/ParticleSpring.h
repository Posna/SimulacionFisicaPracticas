#pragma once
#include "ParticleForceGenerator.h"
class ParticleSpring: public ParticleForceGenerator
{
	//The other particle the spring is attached to
	Particle* other_;

	//Elasticity const
	float k_;

	float restLength_;
public:
	ParticleSpring(Particle* other, float k, float restLeangth);
	virtual void updateForce(Particle* particle, float t);
	void addConst(float suma) { k_ += suma; }
	virtual ~ParticleSpring();
};

