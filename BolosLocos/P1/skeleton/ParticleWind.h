#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"
class ParticleWind: public ParticleForceGenerator
{
	// Acceleration for wind
	Vector3 wind;
	Vector3 pos;
	float radio;
	Particle* p;
	float giro = 0;
public:
	ParticleWind(const Vector3& pos, float radio) : pos(pos), radio(radio) {
		p = new Particle(radio, Vector4(0, 0, 1, 0), pos, 86400.0f);
	}
	~ParticleWind();
	virtual void updateForce(Particle* particle, float t);
	virtual void updateForce(ParticleRigid* particle, float t);
private:
	
};

