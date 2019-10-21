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

float ParticleWind::distanciaDosPuntos(const Vector3& a, const Vector3& b)
{
	float m = (a.x - b.x) * (a.x - b.x);
	float n = (a.y - b.y) * (a.y - b.y);
	float l = (a.z - b.z) * (a.z - b.z);
	return sqrt(m+n+l);
}
