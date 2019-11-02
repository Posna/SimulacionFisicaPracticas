#pragma once
#include "Particle.h"
class ParticleForceGenerator
{
public: 
	// Overload to provide functionality
	virtual void updateForce(Particle* particle, float t) = 0;
	void setInstantForce(bool b) { instantForce = b; }
	bool isInstant() { return instantForce; }
protected:
	float distanciaDosPuntos(const Vector3& a, const Vector3& b);
private:
	bool instantForce = false;

};

