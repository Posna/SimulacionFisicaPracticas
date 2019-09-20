#include "Particle.h"

Particle::Particle(float radio, Vector4 c, Vector3 p)
{
	PxTransform* t = new PxTransform(p);
	particle = new RenderItem(CreateShape(PxSphereGeometry(radio)), t, c);
}