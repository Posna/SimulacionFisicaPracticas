#pragma once

#define GRAVITY {0.0, -9.8, 0.0}

#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleWind.h"
#include <vector>

class ParticleSystem :
	public Particle
{
public:
	ParticleSystem(Vector3 pos, float minAge, float maxAge, float spawnTime, float gravity = -9.8);
	bool update(float time);
	~ParticleSystem();

private:
	void spawnParticle(float time);
	Vector3 randomVector(Vector3 normal, float radio);

	std::vector<Particle*> particles_;
	ParticleForceRegistry* registry;
	ParticleGravity* gravity_;
	ParticleWind* wind_;
	float minAge_;
	float maxAge_;
	float spawnTime_;
	float currentTime_;
	float age_ = 5000.0f;
};