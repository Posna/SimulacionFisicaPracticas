#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vector3 relativePos = particle[0]->getPos() -
		particle[1]->getPos();
	return relativePos.magnitude();
}
