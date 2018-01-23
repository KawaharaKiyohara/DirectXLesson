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
	//�����G���W�����������B
	//���͋C�ɂ��Ȃ��Ă悢�B
	collisionConfig = new btDefaultCollisionConfiguration();
	//���͋C�ɂ��Ȃ��Ă悢�B
	collisionDispatcher = new	btCollisionDispatcher(collisionConfig);
	//���͋C�ɂ��Ȃ��Ă悢�B
	overlappingPairCache = new btDbvtBroadphase();
	//���͋C�ɂ��Ȃ��Ă悢�B
	constraintSolver = new btSequentialImpulseConstraintSolver;
	//�������[���h���쐬�B
	dynamicWorld = new btDiscreteDynamicsWorld(
		collisionDispatcher,
		overlappingPairCache,
		constraintSolver,
		collisionConfig
		);
	//�������[���h�̏d�͂�ݒ�B
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
