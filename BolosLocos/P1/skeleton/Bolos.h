#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "ParticleRigid.h"
#include <vector>

const int  DISTX = 4;
const int DISTY = -5;

using namespace physx;

class Bolos
{
public:
	Bolos(Vector3 position, int filas, PxPhysics* gP, PxScene* gS);
	~Bolos();
	void update(float time);
	int caidos();
	int numBolos() { return maxBolos; }

private:
	std::vector<ParticleRigid*> bolos_;
	Vector3 position_;
	int maxBolos;
	int caidos_ = 0;
	float timeDown_ = 0.0;
};

