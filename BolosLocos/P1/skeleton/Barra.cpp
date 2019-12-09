#include "Barra.h"

Barra::Barra(): Particle(Vector4(0.0, 0.0, 1.0, 1.0), Vector3(0.0, 1.0, 180.0))
{
	x_ = 0.0f;
	PxShape* shape = CreateShape(PxBoxGeometry(0.5, 0.1, 10));
	particle_ = new RenderItem(shape, t, getColour());
	setAge(86400.0f); //Vida maxima para que no muera
}

bool Barra::update(float time)
{
	timer_ += time;
	Vector3 pos = getPos();
	setPos(Vector3(20*sin(timer_) + x_, pos.y, pos.z));
	Particle::integrate(time);

	return false;
}
