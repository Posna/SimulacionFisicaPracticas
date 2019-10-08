#include "Firework.h"

Firework::Firework(float _age, Vector3 _pos, Vector3 _vel, int rule): Particle(5, age,Vector4(0.5f, 0.5f, 0.5f, 1.0f),_pos), rule_(rule), age(_age)
{
	setVel(_vel, 1);
	initFireworkRules();
	rules[rule]->create(this);
}

void Firework::initFireworkRules()
{
	rules[0] = new FireworkRule();
	rules[0]->setParameters(
		2, // type
		0.5f, 1.4f, // age range
		Vector3(-5, 50, -5), Vector3(5, 60, 5), // velocity range
		0.1 // damping
	);
	Payload* aux = new Payload(2, 50);
	rules[0]->payloads.push_back(aux);
	aux = new Payload(3, 50);
	rules[0]->payloads.push_back(aux);
	aux = new Payload(4, 50);
	rules[0]->payloads.push_back(aux);

	rules[1] = new FireworkRule();
	rules[1]->setParameters(
		3, // type
		0.5f, 1.4f, // age range
		Vector3(-5, 50, -5), Vector3(5, 60, 5), // velocity range
		0.1 // damping
	);
	aux = new Payload(5, 50);
	rules[1]->payloads.push_back(aux);

	rules[2] = new FireworkRule();
	rules[2]->setParameters(
		4, // type
		0.5f, 1.4f, // age range
		Vector3(-5, 50, -5), Vector3(5, 60, 5), // velocity range
		0.1 // damping
	);
	aux = new Payload(6, 50);
	rules[2]->payloads.push_back(aux);
}

bool Firework::update(float t)
{
	if (type_ != FW_UNKNOWN_TYPE) {
		// Update the particle
		integrate(t);
		age -= t;
		if (age < 0.0) {
			type_ = FW_UNKNOWN_TYPE;
			for each (Payload* payload in rules[rule_]->payloads)
			{
				payload->set();
				payload->setPos(getPos());
			}
			free();
		}
		return false;
	}
	else {
		auto v = rules[rule_]->payloads;
		auto aux = v.begin();
		while (!v.empty() && aux != v.end()) {
			bool deleted = false;
			Payload* p = (*aux);
			if (p != nullptr ) {
				p->update(t);
			}
			if (!v.empty() && !deleted)
				aux++;
		}
		return v.empty();
	}
}