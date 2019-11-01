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
	float age = 0;
public:
	ParticleWind(const Vector3& wind, const Vector3& pos, float radio) : wind(wind), pos(pos), radio(radio) {
		p = new Particle(radio, Vector4(0, 0, 1, 0), pos, 3600.0f);
	}
	virtual void updateForce(Particle* particle, float t);
private:
	float distanciaDosPuntos(const Vector3& a, const Vector3& b);
};

