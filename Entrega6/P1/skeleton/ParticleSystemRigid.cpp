#include "ParticleSystemRigid.h"

ParticleSystemRigid::ParticleSystemRigid(PxPhysics* gPhysics, PxScene* gScene,float radio): gPhysics_(gPhysics), radio_(radio), gScene_(gScene) {}

bool ParticleSystemRigid::update(float time)
{
	time_ += time;
	if (NUMAX > numAct && time_ > timeSpawn) {
		PxTransform t = PxTransform(Vector3(0.0, 0.0, 0.0));
		PxShape* p = CreateShape(PxSphereGeometry(radio_));
		PxRigidDynamic* particle = gPhysics_->createRigidDynamic(t);
		particle->attachShape(*p);
		PxRigidBodyExt::updateMassAndInertia(*particle, 1.0);
		gScene_->addActor(*particle);
		float vel = (float)(rand() % (int)(20 * 100) + (int)(10 * 100)) / 100.0;
		Vector3 aux = randomVector();
		particle->addForce(aux * vel);
		numAct++;
		time_ = 0.0;
	}
	return false;
}

void ParticleSystemRigid::spawnParticle(float time)
{
}

Vector3 ParticleSystemRigid::randomVector()
{
	int ang = (rand() % 360);
	float angR = ((float)ang * 3.14159265f) / 180.0f;
	float x = cos(angR);
	float y = 10;//(float)(rand() % 20)/10.0f;
	float z = sin(angR);
	return Vector3(x, y, z);
}