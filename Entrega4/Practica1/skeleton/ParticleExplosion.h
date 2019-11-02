#pragma once
#include "ParticleForceGenerator.h"
class ParticleExplosion: public ParticleForceGenerator
{
	// Acceleration for wind
	Vector3 pos;
	float radio;
	Particle* p;
public:
	ParticleExplosion(const Vector3& pos, float radio) : pos(pos), radio(radio) {
		p = new Particle(radio, Vector4(1, 0, 0, 0), pos, 3600.0f);
	}
	virtual void updateForce(Particle* particle, float t);
};

