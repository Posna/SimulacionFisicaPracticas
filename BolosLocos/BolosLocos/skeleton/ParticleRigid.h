#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

class ParticleRigid
{
public:
	ParticleRigid(PxPhysics* gPhysics, PxScene* gScene, float radio, Vector3 position = Vector3(0.0), float age = 10.0);
	ParticleRigid(PxPhysics* gPhysics, PxScene* gScene, float x, float y, float z, Vector3 position = Vector3(0.0), float age = 10.0);
	~ParticleRigid();
	bool update(float t);
	Vector3 getPosition();
	void setPosition(Vector3 pos);
	void addForce(Vector3 vec, float imp, PxForceMode::Enum mode = PxForceMode::eFORCE);
	PxRigidDynamic* particle_;
private:
	PxPhysics* gPhysics_;
	PxScene* gScene_;
	PxTransform* t_;

	float age_;
};

