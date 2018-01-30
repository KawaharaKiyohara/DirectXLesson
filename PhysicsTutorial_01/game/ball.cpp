#include "stdafx.h"
#include "game.h"
#include "ball.h"


Ball::Ball()
{
}


Ball::~Ball()
{
	game->GetPhysicsWorld()->RemoveRigidBody(&m_rigidBody);
}
void Ball::Init(const D3DXVECTOR3& pos, float mass)
{
	m_skinModelData.LoadModelData("Assets/modelData/ball.x", nullptr);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&game->GetLight());
	m_position = pos;
	m_sphereCollider.Create(0.05f);
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_sphereCollider;
	rbInfo.localInertia = { 0.0f, 1.0f, 0.0f };
	rbInfo.mass = mass;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	m_rigidBody.Create(rbInfo);

	game->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
}
void Ball::Update()
{
	//物理シミュレーションの結果を受け取る。
	btDefaultMotionState* motionState = m_rigidBody.GetMotionState();
	btTransform wTrans;
	motionState->getWorldTransform(wTrans);
	m_position = (D3DXVECTOR3)wTrans.getOrigin();
	m_rotation = (D3DXQUATERNION)wTrans.getRotation();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}
void Ball::Draw()
{
	m_skinModel.Draw(
		&game->GetCamera()->GetViewMatrix(),
		&game->GetCamera()->GetProjectionMatrix()
	);
}