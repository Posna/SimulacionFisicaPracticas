#include "ParticleRigid.h"

ParticleRigid::ParticleRigid(PxPhysics* gPhysics, PxScene* gScene, float radio, Vector3 position, float age): age_(age),
	gPhysics_(gPhysics), gScene_(gScene)
{
	t_ = new PxTransform(position);
	PxShape* p = CreateShape(PxSphereGeometry(radio));
	particle_ = gPhysics_->createRigidDynamic(*t_);
	particle_->attachShape(*p);
	PxRigidBodyExt::updateMassAndInertia(*particle_, 1.0);
	gScene_->addActor(*particle_);
}

ParticleRigid::ParticleRigid(PxPhysics* gPhysics, PxScene* gScene, float x, float y, float z, Vector3 position, float age): age_(age),
gPhysics_(gPhysics), gScene_(gScene)
{
	t_ = new PxTransform(position);
	PxShape* p = CreateShape(PxBoxGeometry(x, y, z));
	particle_ = gPhysics_->createRigidDynamic(*t_);
	particle_->attachShape(*p);
	PxRigidBodyExt::updateMassAndInertia(*particle_, 1.0);
	gScene_->addActor(*particle_);
}

ParticleRigid::~ParticleRigid()
{
	
	particle_->release();
	delete t_;
}

bool ParticleRigid::update(float t)
{
	age_ -= t;
	return age_ < 0;
}

Vector3 ParticleRigid::getPosition()
{
	return particle_->getGlobalPose().p;
	//return t_->p;
}

void ParticleRigid::setPosition(Vector3 pos)
{
	t_->p = pos;
}

void ParticleRigid::addForce(Vector3 vec, float imp, PxForceMode::Enum mode)
{
	particle_->addForce(vec * imp, mode);
}

