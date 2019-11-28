#include "ParticleExplosion.h"

void ParticleExplosion::updateForce(Particle* particle, float t)
{
	float dist = distanciaDosPuntos(pos, particle->getPos());
	if (dist < radio) {
		Vector3 vEntrePuntos = particle->getPos() - pos;
		particle->addForce(vEntrePuntos*(radio/dist)*10);
	}
}
