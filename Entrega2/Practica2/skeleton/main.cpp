#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "Firework.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
Particle* p;
std::vector<Particle*> particle;
std::vector<Firework*> fireworks;

void FireworksUpdate(float t)
{
	auto aux = fireworks.begin();
	while (!fireworks.empty() && aux != fireworks.end()) {
		bool deleted = false;
		Firework* p = (*aux);
		if (p != nullptr && p->update(t)) {
			fireworks.erase(aux);
			delete p;
			aux = fireworks.begin();
			deleted = true;
		}
		if (!fireworks.empty() && !deleted)
			aux++;
	}
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	// ------------------------------------------------------
	//p = new Particle(10, Vector3(10, 10, 10));
	//fireworks.push_back(new Firework(30, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 0));
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
	//	if (p != nullptr && p->update(t)) {
	//		particle.erase(particle.begin());
	//		delete p;
	//		aux = particle.begin();
	//	}
	//	if(!particle.empty())
	//		aux++;
	//}
	FireworksUpdate(t);
	//p->update(t);
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
	particle.clear();

	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'Q':
	{
		/*Particle* p = new Particle(1, Vector4(0, 0, 0, 1), GetCamera()->getEye());
		p->setVel(GetCamera()->getDir(), 50);
		particle.push_back(p);*/
		fireworks.push_back(new Firework(30, Vector3(), Vector3(), 0));
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


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}