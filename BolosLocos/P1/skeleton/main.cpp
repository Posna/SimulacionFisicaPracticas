#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <iostream>
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
#include "Barra.h"


using namespace physx;

const float TIME_MAX = 5.0f;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

ParticleSystemRigid* fuenteI;
ParticleSystemRigid* fuenteD;
ParticleSystemRigid* fuenteC;

std::vector<Particle*>particle;

enum Fuerzas { Wind1, Wind2, Wind3 };
std::vector<ParticleForceGenerator*> fuerzas;
ParticleAnchoredSpring* anchSpring;
ParticleSpring* spring1;
ParticleSpring* spring2;
ParticleBuoyancy* flotacion;
ParticleCable* cable;
ParticleCable* cable1;
ParticleCable* cable2;
ParticleContact* contacto;
ParticleContact* contacto1;
ParticleContact* contacto2;
ParticleContact* contacto3;
//ParticleRod* barra;
Particle* explosion;
Bolos* b;
Barra* barra1;


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
bool puedeTirar = true;

int numBolas_ = 2;

//Parte para los rigids
int numAct = 0;

bool complete = true;

float timeSpawn = 0.5f;
float time = 0;
int level_ = 0;

PxTransform* t;
PxShape* pShape;
std::vector<PxRigidStatic*> particleRigid;

PxTransform* t1;
PxShape* pShape1;
PxRigidDynamic* particleRigid1;

ParticleRigid* bola = nullptr;
ParticleRigid* muelle4;

ParticleRigid* baseCuerdas;
ParticleRigid* rompeBolas;
ParticleRigid* rompeBolas1;
ParticleRigid* rompeBolas2;



void deleteScene5() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete b;
	delete barra1;
	delete contacto3;
	delete contacto2;
	delete contacto1;
	delete baseCuerdas;
	delete rompeBolas;
	delete rompeBolas1;
	delete rompeBolas2;
}

void Scene5Update(float t) {
	cable->addContact(contacto1, 0);
	contacto1->resolve(t);
	cable1->addContact(contacto2, 0);
	contacto2->resolve(t);
	cable2->addContact(contacto3, 0);
	contacto3->resolve(t);
}

void Scene5() {
	t = new PxTransform(Vector3(0.0, 0.0, 150.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 200));
	PxRigidStatic* particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	/*t = new PxTransform(Vector3(0.0, -14.9, 225.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 500));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);*/

	t = new PxTransform(Vector3(0.0, 95.0f, 40.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 25));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);
	//muelle4->particle_->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	baseCuerdas = new ParticleRigid(gPhysics, gScene, 10.0f, 1.0f, 10.0f, Vector3(0.0f, 100.0f, 40.0f), 86400.0f);
	rompeBolas = new ParticleRigid(gPhysics, gScene, 5.0f, Vector3(-5.0f, 10.0f, 35.0f), 86400.0f);
	rompeBolas1 = new ParticleRigid(gPhysics, gScene, 5.0f, Vector3(0.0f, 10.0f, 40.0f), 86400.0f);
	rompeBolas2 = new ParticleRigid(gPhysics, gScene, 5.0f, Vector3(5.0f, 10.0f, 35.0f), 86400.0f);
	contacto1 = new ParticleContact(rompeBolas, baseCuerdas);
	contacto2 = new ParticleContact(rompeBolas1, baseCuerdas);
	contacto3 = new ParticleContact(rompeBolas2, baseCuerdas);
	cable = new ParticleCable(rompeBolas, baseCuerdas, 80);
	cable1 = new ParticleCable(rompeBolas1, baseCuerdas, 80);
	cable2 = new ParticleCable(rompeBolas2, baseCuerdas, 80);

	//bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));
}

void deleteScene4() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	registry.clear();
	delete fuerzas[0];
	delete muelle4;
	fuerzas.clear();
	delete barra1;
	delete b;
}

void Scene4Update(float t) {
	muelle4->update(t);
	registry.updateForces(t);
}

void Scene4() {
	t = new PxTransform(Vector3(0.0, -14.9, -25.0));
	pShape = CreateShape(PxBoxGeometry(25, 15, 75));
	PxRigidStatic* particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(0.0, -14.9, 225.0));
	pShape = CreateShape(PxBoxGeometry(25, 15, 75));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(26.0, 0.0, 100.0));
	pShape = CreateShape(PxBoxGeometry(1, 200, 75));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(-26.0, 0.0, 100.0));
	pShape = CreateShape(PxBoxGeometry(1, 200, 75));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	PxQuat g = PxQuat(3.14 / 9.0, Vector3(1.0, 0.0, 0.0));
	t = new PxTransform(Vector3(0.0, -5.0, 165.0), g);
	pShape = CreateShape(PxBoxGeometry(25, 1, 20));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);
	muelle4 = new ParticleRigid(gPhysics, gScene, 24.9f, 9.9f, 25.0f, Vector3(0.0, 0.0, 100.0), 86400.0f);
	fuerzas.push_back(new ParticleBuoyancy(-10.0f, 90990.1f, 20.0f));
	//muelle4->particle_->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	registry.add(muelle4, fuerzas[0]);

	//bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));
}

void deleteScene3() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete b;
	delete barra1;
	for each (ParticleWind * var in fuerzas)
	{
		delete var;
	}
	fuerzas.clear();
	registry.clear();
}

void Scene3Update(float t) {
	registry.updateForces(t);
}

void Scene3() {
	fuerzas.push_back(new ParticleWind(Vector3(-25, 0, 80), 15));

	fuerzas.push_back(new ParticleWind(Vector3(25, 0, 80), 15));

	fuerzas.push_back(new ParticleWind(Vector3(0, -7, 140), 20));
	//fuerzas[Explosion]->setInstantForce(true);

	t = new PxTransform(Vector3(0.0, 0.0, -25.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 75));
	PxRigidStatic* particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(0.0, 0.0, 225.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 75));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(20.0, 0.0, 100.0));
	pShape = CreateShape(PxBoxGeometry(5, 1, 70));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(-20.0, 0.0, 100.0));
	pShape = CreateShape(PxBoxGeometry(5, 1, 70));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);


	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);

	registry.add(bola, fuerzas[0]);
	registry.add(bola, fuerzas[1]);
	registry.add(bola, fuerzas[2]);

	//bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));
}


void deleteScene2() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete b;
	delete barra1;
	delete fuenteC;
	delete fuenteD;
	delete fuenteI;
}

void Scene2Update(float t) {
	fuenteI->update(t);
	fuenteD->update(t);
	fuenteC->update(t);
}

void Scene2() {
	t = new PxTransform(Vector3(0.0, 0.0, -25.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 75));
	PxRigidStatic* particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	t = new PxTransform(Vector3(0.0, 0.0, 225.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 75));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	PxQuat g = PxQuat(3.14 / 9.0, Vector3(1.0, 0.0, 0.0));
	t = new PxTransform(Vector3(0.0, -5.0, 160.0), g);
	pShape = CreateShape(PxBoxGeometry(25, 1, 20));
	particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);

	barra1 = new Barra();

	fuenteI = new ParticleSystemRigid(gPhysics, gScene, Vector3(7.0, 30.0, 100.0), 1.0f);
	fuenteC = new ParticleSystemRigid(gPhysics, gScene, Vector3(0.0, 30.0, 100.0), 1.0f);
	fuenteD = new ParticleSystemRigid(gPhysics, gScene, Vector3(-7.0, 30.0, 100.0), 1.0f);

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);

	//bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));
}

void deleteScene1() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete b;
	delete barra1;
}

void Scene1Update(float t) {

}


void Scene1() {

	t = new PxTransform(Vector3(0.0, 0.0, 150.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 200));
	PxRigidStatic* particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);
	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);
	if (bola == nullptr)
		bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));

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
	sceneDesc.gravity = PxVec3(0.0f, -98.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	
	// ------------------------------------------------------
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	if (complete) {
		switch (level_)
		{
		case 0:
			Scene1();
			break;
		case 1:
			deleteScene1();
			Scene2();
			break;
		case 2:
			deleteScene2();
			Scene3();
			break;
		case 3:
			deleteScene3();
			Scene4();
			break;
		case 4:
			deleteScene4();
			Scene5();
			break;
		default:
			break;
		}
		complete = false;
	}
	switch (level_)
	{
	case 0:
		Scene1Update(t);
		break;
	case 1:
		Scene2Update(t);
		break;
	case 2:
		Scene3Update(t);
		break;
	case 3:
		Scene4Update(t);
		break;
	case 4:
		Scene5Update(t);
		break;
	default:
		break;
	}

	bola->update(t);
	barra1->update(t);
	if (explosion != nullptr && explosion->update(t)) {
		delete explosion;
		explosion = nullptr;
	}
	b->update(t);
	if (b->caidos() == b->numBolos()) {
		time += t;
		if (time > 3.0f) {
			complete = true;
			level_++;
			if (level_ == 5) {
				deleteScene5();
			}
			level_ = level_ % 5;
			time = 0;
		}
	}
	
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
		//p1->setVel(-p2->getPos() + p1->getPos());
		break;
	}
	case 'Q':
	{
		level_++;
		if (level_ == 5) {
			deleteScene5();
		}
		level_ = level_ % 5;
		complete = true;
		//anchSpring->addConst(-0.01f);
		break;
	}
	case 'R':
	{
		system("CLS");
		std::cout << b->caidos();
		//Scene1();
		//flotacion->addVolume(+0.01f);
		break;
	}
	case 'X':
	{
		fuenteI->addForce(Vector3(2.0, 5.0, 0.0), 15);
		if (explosion != nullptr)
			delete explosion;
		explosion = new Particle(15, Vector4(1.0, 0.0, 0.0, 0.0), Vector3(2.0, 5.0, 0.0), 2.0f);
		//flotacion->addVolume(-0.01f);
		break;
	}
	case 'C':
	{
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
	case ' ': {

		if (level_ == 2) {
			registry.clear();
			delete bola;
			bola = new ParticleRigid(gPhysics, gScene, 5, barra1->getPos());
			registry.add(bola, fuerzas[0]);
			registry.add(bola, fuerzas[1]);
			registry.add(bola, fuerzas[2]);
		}
		else {
			delete bola;
			bola = new ParticleRigid(gPhysics, gScene, 5, barra1->getPos());
		}
		bola->addForce(Vector3(0.0, 0.0, -1.0), 99999, PxForceMode::eIMPULSE);
		//p2->setVel(Vector3(1.0f, 0.0f, 0.0f), 2);
		//p3->setVel(Vector3(1.0f, 0.0f, 0.0f), 1);
		//registry.remove(p1, fuerzas[Gravity2]);
		//registry.remove(p2, fuerzas[Gravity1]);
		//registry.remove(p3, fuerzas[Gravity2]);
		break;
	}
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