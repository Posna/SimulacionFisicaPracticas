#pragma once
#include "Particle.h"
#include <random>

#define GRAVITY {0.0, -9.8, 0.0}
enum Types { FW_UNKNOWN_TYPE, NORMAL_TYPE };

class Firework :
	public Particle
{
public:

	struct FireworkRule
	{
		struct Payload {
			// Type of payload it has (what it will generate)
			unsigned type;

			unsigned count;

			void set(unsigned _type, unsigned _count)
			{
				type = _type;
				count = _count;
			}
			Payload(unsigned _type, unsigned _count) {
				set(_type, _count);
			}
		};
		// Type of firework configured
		unsigned type;

		float minAge;
		float maxAge;

		// Minimum relative velocity
		Vector3 minVelocity;
		Vector3 maxVelocity;
		float damping;
		std::vector<Payload> payloads;

		FireworkRule() {}
		void setParameters(unsigned _type, float _minAge, float _maxAge, Vector3 _minVel, Vector3 _maxVel, float _damping) {
			type = _type;
			minAge = _minAge;
			maxAge = _maxAge;
			minVelocity = _minVel;
			maxVelocity = _maxVel;
			damping = _damping;
		}

		void create(Firework* firework, const Firework* parent = NULL)
			const
		{
			firework->type_ = type;
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

	FireworkRule** rules = new FireworkRule*[2];
	Firework(float _age, Vector3 _pos, Vector3 _vel);
	FireworkRule* GetRuleFromType(unsigned type_);
	void initFireworkRules();
	unsigned type_;
	bool update(float t);
	void FireworksCreate(unsigned type, const Firework* parent);
	Firework* create(unsigned type, unsigned count, Firework* f);
	// Previous code
	bool isActive() const
	{
		return type_ != FW_UNKNOWN_TYPE;
	}
	void setInactive()
	{
		type_ = FW_UNKNOWN_TYPE;
	}
private:
	// Time left for the firework to detonate
	// When age reaches zero, the particle disappears and delivers the payload
	float age;
};