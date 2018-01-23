#include "stdafx.h"
#include "Physics/RigidBody.h"
#include "Physics/ICollider.h"

RigidBody::RigidBody() :
	rigidBody(NULL),
	myMotionState(NULL)
{
}


RigidBody::~RigidBody()
{
	Release();
}
void RigidBody::Release()
{
	delete rigidBody;
	delete myMotionState;
	rigidBody = NULL;
	myMotionState = NULL;
}
void RigidBody::Create(RigidBodyInfo& rbInfo)
{
	Release();
	//���̂̏����ʒu��ݒ�B
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	//���[�V�����X�e�[�g���쐬�B
	//���̂ƍ��W�̂��]�̂������s�����߂̃C���^�[�t�F�[�X�B
	myMotionState = new btDefaultMotionState;
	myMotionState->setWorldTransform(transform);
	//���̂��쐬���邽�߂̏���ݒ�B
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(
		rbInfo.mass, 
		myMotionState, 
		rbInfo.collider->GetBody(), 
		btVector3(rbInfo.localInertia.x, rbInfo.localInertia.y, rbInfo.localInertia.z)
	);
	//���̂��쐬�B
	rigidBody = new btRigidBody(btRbInfo);
}
