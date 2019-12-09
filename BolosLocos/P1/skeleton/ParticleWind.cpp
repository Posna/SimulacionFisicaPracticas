#include "ParticleWind.h"
#include <math.h>

ParticleWind::~ParticleWind()
{
	delete p;
}

void ParticleWind::updateForce(Particle* particle, float t)
{
	p->update(t);
	wind = Vector3(cos(p->getAge() / 1000), 0.0f, sin(p->getAge() / 1000));
	float disPP = distanciaDosPuntos(particle->getPos(), pos);
	if (disPP < radio) {
		if (particle->hasInfiniteMass()) return;
		particle->addForce(wind * 10);
	}

}

void ParticleWind::updateForce(ParticleRigid* particle, float t)
{
	p->update(t);
	//wind = Vector3(cos(p->getAge()/1000), 0.0f, sin(p->getAge()/1000));
	float disPP = distanciaDosPuntos(particle->getPosition(), pos);
	if (disPP < radio) {
		if (particle->particle_->getMass() == 0.0) return;
		particle->addForce(particle->getPosition()-pos, 9999);
	}

}
