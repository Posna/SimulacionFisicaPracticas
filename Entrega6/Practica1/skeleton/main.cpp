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
	fuerzas.push_back(new ParticleGravity(Vector3(-10.0f, 9.8, 5.0f)));

	fuerzas.push_back(new ParticleGravity(Vector3(10.0f, -9.8, -5.0f)));

	fuerzas.push_back(new ParticleWind(Vector3(0, -6000, 0), 10));
	fuerzas[Wind]->setInstantForce(true);

	fuerzas.push_back(new ParticleExplosion(Vector3(0, -6000, 0), 20));
	fuerzas[Explosion]->setInstantForce(true);

	fuerzas.push_back(new ParticleGravity(Vector3(0.0f, -9.8f, 0.0f)));


	prueba = new ParticleSystemRigid(gPhysics, gScene);

	t = new PxTransform(Vector3(0.0, 0.0, 0.0));
	pShape = CreateShape(PxBoxGeometry(100, 1, 100));
	particleRigid = gPhysics->createRigidStatic(*t);
	particleRigid->attachShape(*pShape);
	gScene->addActor(*particleRigid);

	// ------------------------------------------------------
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	prueba->update(t);
	if (explosion != nullptr && explosion->update(t)) {
		delete explosion;
		explosion = nullptr;
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
	
	case 'X':
	{
		prueba->addForce(Vector3(2.0, 5.0, 0.0), 15);
		if (explosion != nullptr)
			delete explosion;
		explosion = new Particle(15, Vector4(1.0, 0.0, 0.0, 0.0), Vector3(2.0, 5.0, 0.0), 2.0f);
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