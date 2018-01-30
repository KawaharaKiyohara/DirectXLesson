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
	//剛体の初期位置を設定。
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	//モーションステートを作成。
	//剛体と座標のや回転のやり取りを行うためのインターフェース。
	myMotionState = new btDefaultMotionState;
	myMotionState->setWorldTransform(transform);
	//剛体を作成するための情報を設定。
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(
		rbInfo.mass, 
		myMotionState, 
		rbInfo.collider->GetBody(), 
		btVector3(rbInfo.localInertia.x, rbInfo.localInertia.y, rbInfo.localInertia.z)
	);
	//剛体を作成。
	rigidBody = new btRigidBody(btRbInfo);
}
