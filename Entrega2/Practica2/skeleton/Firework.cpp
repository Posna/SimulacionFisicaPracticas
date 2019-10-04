#include "Firework.h"

Firework::Firework(float _age, Vector3 _pos, Vector3 _vel): Particle(_age, _pos)
{
	setVel(_vel, 1);
}

Firework::FireworkRule* Firework::GetRuleFromType(unsigned type_)
{
	return rules[type_];
}

void Firework::initFireworkRules()
{
	rules[0]->setParameters(
		1, // type
		0.5f, 1.4f, // age range
		Vector3(-5, 25, -5), Vector3(5, 28, 5), // velocity range
		0.1 // damping
	);
	rules[0]->payloads.push_back(
		FireworkRule::Payload(3, 5));
	rules[0]->payloads.push_back(
		FireworkRule::Payload(5, 5));
}

bool Firework::update(float t)
{
	// Update the particle
	integrate(t);
	age -= t;
	return (age < 0);
}

void Firework::FireworksCreate(unsigned type, const Firework* parent)
{
	FireworkRule* rule = GetRuleFromType(type);
	Firework* newFirework = AllocNewFirework();
	rule->create(newFirework, parent);
}

Firework* Firework::create(unsigned type, unsigned count, Firework* f)
{
	/*return new Firework()*/
}
