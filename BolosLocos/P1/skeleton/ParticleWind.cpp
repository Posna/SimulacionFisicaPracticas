#include "ParticleWind.h"
#include <math.h>

void ParticleWind::updateForce(Particle* particle, float t)
{
	p->update(t);
	wind = Vector3(cos(p->getAge()/1000), 0.0f, sin(p->getAge()/1000));
	float disPP = distanciaDosPuntos(particle->getPos(), pos);
	if (disPP < radio) {
		if (particle->hasInfiniteMass()) return;
		particle->addForce(wind*10);
	}

}