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

enum Fuerzas { Wind1, Wind2, Wind3};
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
float time;
int level_ = 1;

PxTransform* t;
PxShape* pShape;
std::vector<PxRigidStatic*> particleRigid;

PxTransform* t1;
PxShape* pShape1;
PxRigidDynamic* particleRigid1;

ParticleRigid* bola;
ParticleRigid* muelle4;


void deleteScene6() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete b;
}

void Scene6Update(float t) {
	muelle4->update(t);
	registry.updateForces(t);
}

void Scene6() {
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

	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);
	//muelle4->particle_->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

	//bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));
}


void deleteScene5() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete b;
}

void Scene5Update(float t) {
	muelle4->update(t);
	registry.updateForces(t);
}

void Scene5() {
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

	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);
	//muelle4->particle_->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

	//bola = new ParticleRigid(gPhysics, gScene, 5, Vector3(0.0, 0.0, 120.0));
}

void deleteScene4() {
	for each (PxRigidStatic * var in particleRigid)
	{
		var->release();
	}
	particleRigid.clear();
	delete fuerzas[1];
	fuerzas.clear();
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
	for each (ParticleWind* var in fuerzas)
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
	for each (PxRigidStatic* var in particleRigid)
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

	t = new PxTransform(Vector3(0.0, 0.0, 150.0));
	pShape = CreateShape(PxBoxGeometry(25, 1, 200));
	PxRigidStatic* particleRigidAux = gPhysics->createRigidStatic(*t);
	particleRigidAux->attachShape(*pShape);
	gScene->addActor(*particleRigidAux);
	particleRigid.push_back(particleRigidAux);
	barra1 = new Barra();

	b = new Bolos(Vector3(0.0, 5.0, 0.0), 5, gPhysics, gScene);

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
	//Init forces

	//Scene1();
	
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
	if (complete) {
		switch (level_)
		{
		case 1:
			Scene1();
			break;
		case 2:
			deleteScene1();
			Scene2();
			break;
		case 3:
			deleteScene2();
			Scene3();
			break;
		case 4:
			deleteScene3();
			Scene4();
			break;
		default:
			break;
		}
		complete = false;
	}
	switch (level_)
	{
	case 1:
		Scene1Update(t);
		break;
	case 2:
		Scene2Update(t);
		break;
	case 3:
		Scene3Update(t);
		break;

	case 4:
		Scene4Update(t);
		break;
	default:
		break;
	}
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
	bola->update(t);
	barra1->update(t);
	if (explosion != nullptr && explosion->update(t)) {
		delete explosion;
		explosion = nullptr;
	}
	b->update(t);
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
		//p1->setVel(-p2->getPos() + p1->getPos());
		break;
	}
	case 'Q':
	{
		level_++;
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
	case ' ': {

		if (level_ == 3) {
			registry.clear();
			delete bola;
			bola = new ParticleRigid(gPhysics, gScene, 5, barra1->getPos());
			registry.add(bola, fuerzas[0]);
			registry.add(bola, fuerzas[1]);
			registry.add(bola, fuerzas[2]);
			bola->addForce(Vector3(0.0, 0.0, -1.0), 99999, PxForceMode::eIMPULSE);
		}
		else {
			delete bola;
			bola = new ParticleRigid(gPhysics, gScene, 5, barra1->getPos());
			bola->addForce(Vector3(0.0, 0.0, -1.0), 99999, PxForceMode::eIMPULSE);
		}
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