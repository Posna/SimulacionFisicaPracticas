#pragma once
#include "Particle.h"
#include <random>

#define GRAVITY Vector3{0.0, -9.8, 0.0}
#define toRadians 3.1415 / 180
enum Types { FW_UNKNOWN_TYPE, NORMAL_TYPE, CIRCULO_XZ, CIRCULO_XY, CIRCULO_ZY, CILINDRO, ESFERA};
enum FireWorkTypes {ATOMO};

class Firework :
	public Particle
{
public:

	struct Payload {
		Payload(unsigned _type, unsigned _count): type(_type), count(_count)  {
			//Colores aleatorios 
			color.x = ((float)(rand() % 100))/ 100.0;
			color.y = ((float)(rand() % 100)) / 100.0;
			color.z = ((float)(rand() % 100)) / 100.0;
			color.w = 1.0;
		}
		// Type of payload it has (what it will generate)
		Vector4 color;
		std::vector<Particle*> particulas;
		unsigned type;
		unsigned count;

		~Payload() {
			while (particulas.begin() != particulas.end())
			{
				Particle* p = (*particulas.begin());
				particulas.erase(particulas.begin());
				delete p;
			}
		}

		void set()
		{
			switch (type)
			{
			case CIRCULO_XZ: {
				int ang = 360 / count;
				for (int i = 0; i < count; i++) {
					Particle* p = new Particle(1, 2.0, color, Vector3(0.0f, 0.0f, 0.0f));
					p->setVel(Vector3(cos(i * ang * toRadians),1.5, sin(i * ang * toRadians)), 100);
					p->setAcceleration(GRAVITY/4);
					p->setMass(0.001f);
					particulas.push_back(p);
				}
				break;
			}
			case CIRCULO_XY: {
				int ang = 360 / count;
				for (int i = 0; i < count; i++) {
					Particle* p = new Particle(1, 2.0, color, Vector3(0.0f, 0.0f, 0.0f));
					p->setVel(Vector3(cos(i * ang * toRadians), sin(i * ang * toRadians)+1.5, 0), 100);
					p->setAcceleration(GRAVITY/4);
					p->setMass(0.001f);
					particulas.push_back(p);
				}
				break;
			}
			case CIRCULO_ZY: {
				int ang = 360 / count;
				for (int i = 0; i < count; i++) {
					Particle* p = new Particle(1, 2.0, color, Vector3(0.0f, 0.0f, 0.0f));
					p->setVel(Vector3(0, cos(i * ang * toRadians)+1.5, sin(i * ang * toRadians)), 100);
					p->setAcceleration(GRAVITY/4);
					p->setMass(0.001f);
					particulas.push_back(p);
				}
				break;
			}
			case CILINDRO: {
				int ang = 360 / count;
				for (int j = 0; j < count; j++) {
					for (int i = 0; i < count; i++) {
						Particle* p = new Particle(1, 2.0, color, Vector3(0.0f, 0.0f, 0.0f));
						p->setVel(Vector3(cos(i * ang * toRadians), cos(j * ang * toRadians) + 1.5, sin(i * ang * toRadians)), 100);
						p->setAcceleration(GRAVITY / 4);
						p->setMass(0.001f);
						particulas.push_back(p);
					}
				}
				break;
			}
			case ESFERA: {
				int ang = 360 / count;
				for (int j = 0; j < count; j++) {
					for (int i = 0; i < count; i++) {
						Particle* p = new Particle(1, 2.0, color, Vector3(0.0f, 0.0f, 0.0f));
						p->setVel(Vector3(cos(2*i * ang * toRadians)*sin(j * ang * toRadians), cos((-3.1415/2)*j * ang * toRadians)*cos( j * ang * toRadians)  + 1.5, sin(2*i * ang * toRadians)*sin(j * ang * toRadians)), 50);
						p->setAcceleration(GRAVITY / 4);
						p->setMass(0.001f);
						particulas.push_back(p);
					}
				}
				break;
			}
			default:
				break;
			}
		}

		void setPos(Vector3 pos) {
			for each (Particle* p in particulas)
			{
				p->setPos(pos);
			}
		}
		bool update(float time) {
			auto aux = particulas.begin();
			while (!particulas.empty() && aux != particulas.end()) {
				bool deleted = false;
				Particle* p = (*aux);
				if (p != nullptr && p->update(time)) {
					particulas.erase(aux);
					delete p;
					aux = particulas.begin();
					deleted = true;
				}
				if (!particulas.empty() && !deleted)
					aux++;
			}
			return particulas.empty();
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
		std::vector<Payload*> payloads;

		~FireworkRule() {
			while (payloads.begin() != payloads.end())
			{
				Payload* p = (*payloads.begin());
				payloads.erase(payloads.begin());
				delete p;
			}
		}

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
			firework->age = (float)(rand() % (int)((maxAge-minAge)*100) + (int)(minAge*100))/100.0;
			Vector3 vel;
			if (parent)
			{ // inherit velocity from parent
				firework->setPos(parent->getPos());
				vel += parent->getVel();
			}
			else
			{
				Vector3 start = Vector3(0.0,0.0,0.0);
				int x = (rand() % 3) - 1;
				start.x = 5.0f * x;
				firework->setPos(start);
				vel = Vector3(0.0f, 0.0f, 0.0f);
			}
			float x, y, z;
			x = (float)(rand() % (int)((maxVelocity.x - minVelocity.x) * 100) + (int)(minVelocity.x * 100)) / 100.0;
			y = (float)(rand() % (int)((maxVelocity.y - minVelocity.y) * 100) + (int)(minVelocity.y * 100)) / 100.0;
			z = (float)(rand() % (int)((maxVelocity.z - minVelocity.z) * 100) + (int)(minVelocity.z * 100)) / 100.0;
			vel += Vector3(x, y, z);
			firework->setVel(vel, 10);
			// Force the mass to 1
			firework->setMass(1);
			firework->setDamping(damping);
			firework->setAcceleration(GRAVITY);
		}
	};

	FireworkRule** rules = new FireworkRule*[3];
	Firework(float _age, Vector3 _pos, Vector3 _vel, int rule);
	void initFireworkRules();
	unsigned type_;
	virtual bool update(float t);
	~Firework() {
		for (int i = 0; i < rules_number; i++) {
			delete rules[i];
		}
		delete [] rules;
	}
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

	int rule_;
	int rules_number = 3;
};