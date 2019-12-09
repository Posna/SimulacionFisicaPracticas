#include "ParticleSystemRigid.h"

ParticleSystemRigid::ParticleSystemRigid(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos, float radio): gPhysics_(gPhysics), radio_(radio), gScene_(gScene), pos_(pos) {}

ParticleSystemRigid::~ParticleSystemRigid()
{
	for each (ParticleRigid* var in particles_)
	{
		delete var;
	}
	particles_.clear();
}

bool ParticleSystemRigid::update(float time)
{
	time_ += time;
	if (NUMAX > numAct && time_ > timeSpawn) {
		ParticleRigid* p = new ParticleRigid(gPhysics_, gScene_, 1.0f, pos_, 2.0f);
		particles_.push_back(p);
		float vel = (float)(rand() % (int)(20 * 100) + (int)(10 * 100)) / 100.0;
		Vector3 aux = randomVector();
		p->addForce(aux, vel);
		numAct++;
		time_ = 0.0;
	}
	bool borra = false;
	auto p = particles_.begin();
	while (p != particles_.end() && !borra)
	{
		borra = (*p)->update(time);
		if(!borra)
			p++;
	}
	if (borra) {
		auto particle = *p;
		particles_.erase(p);
		delete particle;
		numAct--;
	}
	return false;
}

void ParticleSystemRigid::addForce(Vector3 pos, float radio)
{
	for each (ParticleRigid* var in particles_)
	{
		Vector3 posPart = var->getPosition();
		float d = (posPart - pos).magnitude();
		if (d <= radio) {
			var->addForce((posPart - pos), (radio - d) * 5000);
		}
	}
}

void ParticleSystemRigid::spawnParticle(float time)
{
}

Vector3 ParticleSystemRigid::randomVector()
{
	int ang = (rand() % 3);
	ang -= 1;
	//float angR = ((float)ang * 3.14159265f) / 180.0f;
	//float x = cos(angR);
	//float y = 10;//(float)(rand() % 20)/10.0f;
	//float z = sin(angR);
	return Vector3(ang, 1, 0);
}