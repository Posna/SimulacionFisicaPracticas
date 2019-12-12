#pragma once
#include "Particle.h"
class Barra :public Particle
{
public:
	Barra();
	virtual bool update(float time);
private:
	float timer_ = 0.0f;
	int fase_ = 0;
	float x_;
};

