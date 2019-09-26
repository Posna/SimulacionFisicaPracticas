#pragma once
#include "Particle.h"
#include <random>

#define GRAVITY {0.0, -9.8, 0.0}

class Firework :
	public Particle
{
	unsigned type;
	struct Payload {
		// Type of payload it has (what it will generate)
		unsigned type;

		unsigned count;

		void set(unsigned _type, unsigned _count)
		{
			type = _type;
			count = _count;
		}
	};

	struct FireworkRule
	{
		// Type of firework configured
		unsigned type;

		float minAge;
		float maxAge;

		// Minimum relative velocity
		Vector3 minVelocity;
		Vector3 maxVelocity;
		float damping;
		std::vector<Payload> payloads;
		void create(Firework* firework, const Firework* parent = NULL)
			const
		{
			firework->type = type;
			firework->age = (float)(rand() % (int)(minAge*100) + (int)(maxAge*100))/100.0;
			Vector3 vel;
			if (parent)
			{ // inherit velocity from parent
				firework->setPos(parent->getPos());
				vel += parent->getVel();
			}
			else
			{
				Vector3 start;
				int x = (rand() % 3) - 1;
				start.x = 5.0f * x;
				firework->setPos(start);
			}
			float x, y, z;
			x = (float)(rand() % (int)(minVelocity.x * 100) + (int)(maxVelocity.x * 100)) / 100.0;
			y = (float)(rand() % (int)(minVelocity.y * 100) + (int)(maxVelocity.y * 100)) / 100.0;
			z = (float)(rand() % (int)(minVelocity.z * 100) + (int)(maxVelocity.z * 100)) / 100.0;
			vel += Vector3(x, y, z);
			firework->setVel(vel, 1.0);
			// Force the mass to 1
			firework->setMass(1);
			firework->setDamping(damping);
			firework->setAcceleration(GRAVITY);
			//firework->clearAccumulator();
		}

	};
public:
	bool update(float t);
	void FireworksCreate(unsigned type, const Firework* parent);
	// Previous code
	bool isActive() const
	{
		return type != FW_UNKNOWN_TYPE;
	}
	void setInactive()
	{
		type = FW_UNKNOWN_TYPE;
	}
private:
	// Time left for the firework to detonate
	// When age reaches zero, the particle disappears and delivers the payload
	float age;
};