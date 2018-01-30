#include "stdafx.h"
#include "Physics/Physics.h"
#include "Physics/RigidBody.h"

PhysicsWorld::PhysicsWorld()
{
	collisionConfig = NULL;
	collisionDispatcher = NULL;
	overlappingPairCache = NULL;
	constraintSolver = NULL;
	dynamicWorld = NULL;
}


PhysicsWorld::~PhysicsWorld()
{
	delete dynamicWorld;
	delete constraintSolver;
	delete overlappingPairCache;
	delete collisionDispatcher;
	delete collisionConfig;
}
void PhysicsWorld::Init()
{
	//物理エンジンを初期化。
	//今は気にしなくてよい。
	collisionConfig = new btDefaultCollisionConfiguration();
	//今は気にしなくてよい。
	collisionDispatcher = new	btCollisionDispatcher(collisionConfig);
	//今は気にしなくてよい。
	overlappingPairCache = new btDbvtBroadphase();
	//今は気にしなくてよい。
	constraintSolver = new btSequentialImpulseConstraintSolver;
	//物理ワールドを作成。
	dynamicWorld = new btDiscreteDynamicsWorld(
		collisionDispatcher,
		overlappingPairCache,
		constraintSolver,
		collisionConfig
		);
	//物理ワールドの重力を設定。
	dynamicWorld->setGravity(btVector3(0, -10, 0));
}
void PhysicsWorld::Update()
{
	dynamicWorld->stepSimulation(1.0f/60.0f);
}
void PhysicsWorld::AddRigidBody(RigidBody* rb)
{
	dynamicWorld->addRigidBody(rb->GetBody());
}
void PhysicsWorld::RemoveRigidBody(RigidBody* rb)
{
	dynamicWorld->removeRigidBody(rb->GetBody());
}
