#include "Firework.h"

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
