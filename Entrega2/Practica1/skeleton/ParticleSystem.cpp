#include "ParticleSystem.h"
#include <cmath>

ParticleSystem::ParticleSystem(Vector3 pos, float minAge, float maxAge, float spawnTime): Particle(0.0001f,Vector4(0.0f, 0.0f, 0.0f, 1.0f), pos, 50.0f), 
	minAge_(minAge), maxAge_(maxAge), spawnTime_(spawnTime), currentTime_(spawnTime)  {

}

bool ParticleSystem::update(float time)
{
	spawnParticle(time);
	auto aux = particles_.begin();
	while (!particles_.empty() && aux != particles_.end()) {
		bool deleted = false;
		Particle* p = (*aux);
		if (p != nullptr && p->update(time)) {
			particles_.erase(aux);
			delete p;
			aux = particles_.begin();
			deleted = true;
		}
		if (!particles_.empty() && !deleted)
			aux++;
	}
	age_ -= time;
	return age_ < 0.0f;
	return false;
}

ParticleSystem::~ParticleSystem()
{
	particles_.clear();
}

void ParticleSystem::spawnParticle(float time)
{
	if (currentTime_ < 0) {
		float ageAux = (float)(rand() % (int)(maxAge_ * 100) + (int)(minAge_ * 100)) / 100.0;
		Particle* aux = new Particle(1, Vector4(1.0f, 1.0f, 0.0f, 1.0f), position_,ageAux);
		aux->setAcceleration(GRAVITY);
		aux->setMass(0.1f);
		float vel = (float)(rand() % (int)(20 * 100) + (int)(10 * 100)) / 100.0;
		aux->setVel(randomVector(Vector3(0.0f,0.0f,0.0f), 0.0f), vel);
		particles_.push_back(aux);
		currentTime_ = spawnTime_;
	}
	currentTime_ -= time;
}

Vector3 ParticleSystem::randomVector(Vector3 normal, float radio)
{
	int ang = (rand() % 360);
	float angR = ((float)ang * 3.14159265f) / 180.0f;
	float x = cos(angR);
	float y = 10;//(float)(rand() % 20)/10.0f;
	float z = sin(angR);
	return Vector3(x, y, z);
}
