#include "stdafx.h"
#include "game.h"
#include "Door.h"


Door::Door()
{
	
}

Door::~Door()
{
	game->GetPhysicsWorld()->RemoveRigidBody(&m_hashiraRigidBody);
	game->GetPhysicsWorld()->RemoveRigidBody(&m_doorRigidBody);
	if (m_hingeConstraint != nullptr) {
		game->GetPhysicsWorld()->GetDynamicWorld()->removeConstraint(m_hingeConstraint);
		delete m_hingeConstraint;
	}
}
void Door::Init()
{
	//柱を作成。
	m_hashiraSkinModelData.LoadModelData("Assets/modelData/Hashira.X", nullptr);
	m_hashiraSkinModel.Init(&m_hashiraSkinModelData);
	m_hashiraSkinModel.SetLight(&game->GetLight());
	m_hashiraCollider.Create({ 0.01f, 1.5f, 0.01f });
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_hashiraCollider;
	rbInfo.localInertia = { 0.0f, 0.0f, 0.0f };
	rbInfo.mass = 0.0f;
	rbInfo.pos = { 10.0f, 2.75f, 20.0f };
	rbInfo.rot = {0.0f, 0.0f, 0.0f, 1.0f};
	m_hashiraRigidBody.Create(rbInfo);
	//game->GetPhysicsWorld()->AddRigidBody(&m_hashiraRigidBody);

	//ドアを作成。
	m_doorSkinModelData.LoadModelData("Assets/modelData/Door.x", nullptr);
	m_doorSkinModel.Init(&m_doorSkinModelData);
	m_doorSkinModel.SetLight(&game->GetLight());
	m_doorCollider.Create({ 1.0f, 0.5f, 0.2f });
	
	rbInfo.collider = &m_doorCollider;
	rbInfo.localInertia = { 1.0f, 1.0f, 1.0f };
	rbInfo.mass = 10.0f;
	rbInfo.pos = { 10.6f, 2.75f, 20.0f };
	rbInfo.rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_doorRigidBody.Create(rbInfo);
	game->GetPhysicsWorld()->AddRigidBody(&m_doorRigidBody);

	//ヒンジコンストレイントを作成。
	m_hingeConstraint = new btHingeConstraint(
		*m_doorRigidBody.GetBody(),
		{-0.5f, 0.0f, 0.0f},
		{ 0.0f, 1.0f, 0.0f }
	);
	//90度しか開かないようにする。
	m_hingeConstraint->setLimit(-3.14/2.0f, 3.14 / 2.0f);
	game->GetPhysicsWorld()->GetDynamicWorld()->addConstraint(m_hingeConstraint);
}
void Door::Update()
{
	m_hashiraSkinModel.UpdateWorldMatrix(
		{ 10.0f, 2.0f, 20.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{1.0f, 1.0f, 1.0f}
	);

	btDefaultMotionState* motionState = m_doorRigidBody.GetMotionState();
	btTransform trans;
	motionState->getWorldTransform(trans);
	D3DXVECTOR3 pos;
	pos = (D3DXVECTOR3)trans.getOrigin();
	pos.y -= 0.75f;
	D3DXQUATERNION rot;
	rot = (D3DXQUATERNION)trans.getRotation();

	m_doorSkinModel.UpdateWorldMatrix(
		pos,
		rot,
		{ 1.0f, 1.0f, 1.0f }
	);
}
void Door::Draw()
{
	m_hashiraSkinModel.Draw(
		&game->GetCamera()->GetViewMatrix(),
		&game->GetCamera()->GetProjectionMatrix());
	m_doorSkinModel.Draw(
		&game->GetCamera()->GetViewMatrix(),
		&game->GetCamera()->GetProjectionMatrix());
}