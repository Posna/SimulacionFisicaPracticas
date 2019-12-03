#include "Bolos.h"

Bolos::Bolos(Vector3 position, int filas, PxPhysics* gP, PxScene* gS): position_(position)
{
	for (size_t i = 1; i <= filas; i++)
	{
		int x_ = -(i - 1)* DISTX;
		for (int j = 1; j <= i; j++)
		{
			int z = DISTY * (i - 1);
			Vector3 addPos = position + Vector3(x_, 0.0, z);
			ParticleRigid* p = new ParticleRigid(gP, gS, 0.7f, 5.0f, 0.7f, addPos);
			x_ += DISTX*2;
			bolos_.push_back(p);
		}
	}
}
