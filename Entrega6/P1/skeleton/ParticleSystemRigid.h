#pragma once
#define NUMAX 50
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
using namespace physx;

class ParticleSystemRigid
{
public:
	ParticleSystemRigid(PxPhysics* gPhysics, PxScene* gScene, float radio = 1.0);
	bool update(float time);
private:
	void spawnParticle(float time);
	Vector3 randomVector();

	PxPhysics* gPhysics_;
	PxScene* gScene_;
	int numAct = 0;

	float radio_;
	float timeSpawn = 1.0;
	float time_ = 0.0;
};

