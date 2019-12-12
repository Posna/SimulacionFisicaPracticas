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
			ParticleRigid* p = new ParticleRigid(gP, gS, 1.3f, 5.0f, 1.3f, addPos);
			x_ += DISTX*2;
			bolos_.push_back(p);
			p->particle_->putToSleep();
		}
	}
	maxBolos = bolos_.size();
}

Bolos::~Bolos()
{
	int n = bolos_.size();
	for (int i = 0; i < n; i++)
	{
		auto aux = bolos_.begin();
		ParticleRigid* var = *aux;
		bolos_.erase(bolos_.begin());
		delete var;
	}
}

void Bolos::update(float time)
{
	int n = 0;
	std::vector<int> borrador;
	for each (ParticleRigid * var in bolos_)
	{
		if (var->getPosition().y < 3 /*&& (var->particle_->isSleeping() || var->getPosition().y < -5)*/) {
			borrador.push_back(n);
			caidos_++;
		}
		n++;
	}
	for (int i = 0; i < borrador.size(); i++)
	{
		auto aux = bolos_.begin() + borrador[i]-i;
		ParticleRigid* var = *aux;
		bolos_.erase(bolos_.begin() + borrador[i]-i);
		delete var;
	}
}

int Bolos::caidos()
{
	int n = 0;
	Vector3 a;
	for each (ParticleRigid* var in bolos_)
	{
		if (var->getPosition().y < 4)
			n++;
		a = var->getPosition();
	}
	return /*(*bolos_.begin())->particle_->isSleeping(); //*/ caidos_;
}

