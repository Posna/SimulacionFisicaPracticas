#pragma once
#define NUMAX 500
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "ParticleRigid.h"
#include <vector>
using namespace physx;

class ParticleSystemRigid
{
public:
	ParticleSystemRigid(PxPhysics* gPhysics, PxScene* gScene, float radio = 1.0);
	bool update(float time);
	void addForce(Vector3 pos, float radio);
private:
	void spawnParticle(float time);
	Vector3 randomVector();

	PxPhysics* gPhysics_;
	PxScene* gScene_;
	ParticleRigid* particle_;
	std::vector<ParticleRigid*> particles_;
	int numAct = 0;

	float radio_;
	float timeSpawn = 0.01;
	float time_ = 0.0;
};

