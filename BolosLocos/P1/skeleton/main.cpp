#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleForceRegistry.h"
#include "ParticleForceGenerator.h"
#include "ParticleGravity.h"
#include "ParticleExplosion.h"
#include "ParticleWind.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleSpring.h"
#include "ParticleBuoyancy.h"
#include "ParticleCable.h"
#include "ParticleCollisionRegistry.h"
#include "ParticleRod.h"
#include "ParticleSystemRigid.h"
#include "Bolos.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

ParticleSystemRigid* prueba;

std::vector<Particle*>particle;

enum Fuerzas { Gravity1, Gravity2, Wind, Explosion, Gravity3 };
std::vector<ParticleForceGenerator*> fuerzas;
ParticleAnchoredSpring* anchSpring;
ParticleSpring* spring1;
ParticleSpring* spring2;
ParticleBuoyancy* flotacion;
ParticleCable* cable;
ParticleContact* contacto;
ParticleContact* contacto1;
ParticleRod* barra;
Particle* explosion;
Bolos* b;

Particle* p1;
Particle* p2;
Particle* p3;
Particle* p4;
Particle* p;
Particle* anchor;

Particle* barril;
Particle* mar;

ParticleForceRegistry registry;
ParticleCollisionRegistry regCol;

Vector3 anchorPos = Vector3(1.0f, 1.0f, 1.0f);

bool keyP = true;

//Parte para los rigids
int numAct = 0;

float timeSpawn = 0.5f;
float time;

PxTransform* t;
PxShape* pShape;
PxRigidStatic* particleRigid;

PxTransform* t1;
PxShape* pShape1;
PxRigidDynamic* particleRigid1;

void Scene1() {

	fuerzas.push_back(new ParticleGravity(Vector3(-10.0f, 9.8, 5.0f)));

	fuerzas.push_back(new ParticleGravity(Vector3(10.0f, -9.8, -5.0f)));

	fuerzas.push_back(new ParticleWind(Vector3(0, -6000, 0), 10));
	fuerzas[Wind]->setInstantForce(true);

	fuerzas.push_back(new ParticleExplosion(Vector3(0, -6000, 0), 20));
	fuerzas[Explosion]->setInstantForce(true);

	fuerzas.push_back(new ParticleGravity(Vector3(0.0f, -9.8f, 0.0f)));


	//p2 = new Particle(5, Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector3(50, -10, 0), 1000);
	////particle.push_back(p2);
	//regCol.add(p2);
	//p1 = new Particle(5, Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector3(0, -10, 0), 10000);
	//p = new Particle(1);
	//contacto = new ParticleContact(p1, p2);
	//barra = new ParticleRod(p1, p2);
	//particle.push_back(p);
	////particle.push_back(p1);
	//regCol.add(p1);
	//p3 = new Particle(5, Vector4(1.0f, 0.7f, 0.0f, 1.0f), Vector3(50, 10, 0), 10000);
	//p4 = new Particle(5, Vector4(0.0f, 0.7f, 1.0f, 1.0f), Vector3(0, 10, 0), 10000);
	//contacto1 = new ParticleContact(p3, p4);
	//cable = new ParticleCable(p3, p4, 60);

	//prueba = new ParticleSystemRigid(gPhysics, gScene);

	t = new PxTransform(Vector3(0.0, -0.5, 0.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 100));
	particleRigid = gPhysics->createRigidStatic(*t);
	particleRigid->attachShape(*pShape);
	gScene->addActor(*particleRigid);

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);

}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	//Init forces
	
	Scene1();

	/*t1 = new PxTransform(Vector3(0.0, 5.0, 20.0));
	pShape1 = CreateShape(PxBoxGeometry(0.5, 5, 0.5));
	particleRigid1 = gPhysics->createRigidDynamic(*t1);
	particleRigid1->attachShape(*pShape1);
	gScene->addActor(*particleRigid1);*/
	//RenderItem(pShape, particleRigid, Vector4(1.0, 0.0, 1.0, 1.0));
	//cable->addContact(contacto1, 0);
	/*anchSpring = new ParticleAnchoredSpring(&anchorPos, 2.0f, 3.5f);
	spring1 = new ParticleSpring(p3, 2.0f, 3.5f);
	spring2 = new ParticleSpring(p2, 2.0f, 3.5f);


	mar = new Particle(CreateShape(PxBoxGeometry(50.0f, 0.5f, 50.0f)), Vector4(54.0 / 255.0, 106.0 / 255.0, 254.0 / 255.0, 1.0f), Vector3(-100.0f, 0.0f, 0.0f));
	barril = new Particle(CreateShape(PxBoxGeometry(5.0f, 5.0f, 5.0f)), Vector4(139.0 / 255.0, 69.0 / 255.0, 19.0 / 255.0, 1.0f), Vector3(-100.0f, 0.0f, 0.0f));
	flotacion = new ParticleBuoyancy(-2.0f, 0.1f, 0.0f);

	anchor = new Particle(1, Vector4(1.0f, 0.0f, 0.5f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), 10000, true);

	registry.add(p1, anchSpring);
	registry.add(p1, fuerzas[Gravity2]);
	p1->setMass(1.0f);

	registry.add(p2, spring1);
	registry.add(p2, fuerzas[Gravity1]);
	p2->setMass(1.0f);

	registry.add(p3, spring2);
	registry.add(p3, fuerzas[Gravity2]);
	p3->setMass(10.0f);

	registry.add(barril, fuerzas[Gravity3]);
	registry.add(barril, flotacion);
	barril->setMass(5.0f);*/

	// ------------------------------------------------------
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	//Actualiza las particulas y elimina las que sobrepasan el tiempo
	//auto aux = particle.begin();
	//while (!particle.empty() && aux != particle.end()) {
	//	Particle* p = (*aux);
	//	/*if (p != nullptr && p->update(t)) {
	//		particle.erase(aux);
	//		regCol.remove(p);
	//		delete p;
	//		aux = particle.begin();
	//	}
	//	if (!particle.empty())
	//		aux++;*/
	//	p->integrate(t);
	//	aux++;
	//}
	
	//registry.updateForces(t);
	//prueba->update(t);
	if (explosion != nullptr && explosion->update(t)) {
		delete explosion;
		explosion = nullptr;
	}
		//delete explosion;
	//regCol.updateCollisions(t);
	//cable->addContact(contacto, 0);
	/*p2->integrate(t);
	p1->integrate(t);
	p3->integrate(t);
	p4->integrate(t);
	barra->addContact(contacto, 0);
	contacto->resolve(t);
	cable->addContact(contacto1, 0);
	contacto1->resolve(t);

	p->integrate(t);*/
	//ParticleContact pc = ParticleContact(p1, p2);
	//pc.resolve(t);
	//pc = ParticleContact(p2, p);
	//pc.resolve(t);
	//pc = ParticleContact(p1, p);
	//pc.resolve(t);
	/*p3->integrate(t);
	barril->integrate(t);*/
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case '+':
	{
		//anchSpring->addConst(+0.01f);
		p1->setVel(-p2->getPos() + p1->getPos());
		break;
	}
	case '-':
	{
		//anchSpring->addConst(-0.01f);
		break;
	}
	case 'Z':
	{
		Scene1();
		//flotacion->addVolume(+0.01f);
		break;
	}
	case 'X':
	{
		prueba->addForce(Vector3(2.0, 5.0, 0.0), 15);
		if (explosion != nullptr)
			delete explosion;
		explosion = new Particle(15, Vector4(1.0, 0.0, 0.0, 0.0), Vector3(2.0, 5.0, 0.0), 2.0f);
		//flotacion->addVolume(-0.01f);
		break;
	}
	case 'C':
	{
		//Particle* p = new Particle(2);
		p->setVel(Vector3(0.0), 0);
		p->setPos(GetCamera()->getEye());
		p->setVel(GetCamera()->getDir(), 50);
		regCol.add(p);
		//barril->setMass(barril->getMass() + 0.01);
		break;
	}
	case 'B':
		p2->setPos(p2->getPos());
		p2->setVel(Vector3(0.0f), 0);
		p3->setPos(p3->getPos());
		p3->setVel(Vector3(0.0f), 0);
		break;
	case 'V':
	{
		p3->setVel(-p3->getPos(), 2);
		p2->setVel(-p2->getPos(), 2);
		//barril->setMass(barril->getMass() - 0.01);
		break;
	}
	case ' ':
		p2->setVel(Vector3(1.0f, 0.0f, 0.0f), 2);
		p3->setVel(Vector3(1.0f, 0.0f, 0.0f), 1);
		//registry.remove(p1, fuerzas[Gravity2]);
		//registry.remove(p2, fuerzas[Gravity1]);
		//registry.remove(p3, fuerzas[Gravity2]);
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}