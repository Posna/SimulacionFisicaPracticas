#include "ParticleContactGenerator.h"

float ParticleContactGenerator::distanciaDosPuntos(const Vector3& a, const Vector3& b)
{
	float m = (a.x - b.x) * (a.x - b.x);
	float n = (a.y - b.y) * (a.y - b.y);
	float l = (a.z - b.z) * (a.z - b.z);
	return sqrt(m + n + l);
}
