#include "stdafx.h"
#include "Tiger.h"
#include "game.h"

namespace {
	//min����max�܂ł̒l���ԕϐ����Ő��`�⊮�B
	float Lerp(float t, float min, float max)
	{
		return min * (1.0f - t) + max *  t;
	}
}
Tiger::Tiger(SkinModelData* skinModelData)
{
	//���C�g�̏������B
	InitLight();

	//���W�̏������B
	InitPosition();
	m_skinModelData = skinModelData;
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetLight(&light);

	m_boxCollider.Create({ 0.5f, 0.7f, 1.0f });	//Box�R���C�_�[�����B
	//���̂����B
	RigidBodyInfo rbInfo;						//���̂̏����쐬�B
	D3DXQuaternionIdentity(&m_rotation);
	rbInfo.pos = m_position;					//���̂̏����ʒu�B
	rbInfo.rot = m_rotation;					//���̂̏�����]�B
	rbInfo.mass = 1.0f;							//���ʁB
	rbInfo.localInertia = { 1.0f, 1.0f, 1.0f };	//�����B
	rbInfo.collider = &m_boxCollider;
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ��B
	game->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
}
Tiger::~Tiger()
{
	//���̂𕨗����[���h����폜�B
	game->GetPhysicsWorld()->RemoveRigidBody(&m_rigidBody);
}
void Tiger::InitPosition()
{
	//�Ղ̏����ʒu�������_���Ɍ���B
	float t = (rand() % 100) / 100.0f;
	D3DXVECTOR3 basePosition = { 10.0f, 5.0f, 10.0f };
	basePosition.x += Lerp(t, -7.0f, 7.0f);
	t = (rand() % 100) / 100.0f;
	basePosition.y += Lerp(t, 0.0f, 5.0f);
	t = (rand() % 100) / 100.0f;
	basePosition.z += Lerp(t, -7.0f, 7.0f);
	m_position = basePosition;
}
void Tiger::InitLight()
{
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	m_skinModel.SetLight(&light);
}
bool Tiger::Update()
{
	//���[�V�����X�e�[�g���擾�B
	btDefaultMotionState* motionState = m_rigidBody.GetMotionState();
	btTransform transform;
	motionState->getWorldTransform(transform);				//���̂̃g�����X�t�H�[�����擾�B
	m_position = (D3DXVECTOR3)transform.getOrigin();		//���W�𔽉f�B
	m_rotation = (D3DXQUATERNION)transform.getRotation();	//��]�𔽉f�B
	
	m_timer++;
	if (m_timer == 1000) {
		//1000�t���[���Ŏ��S����B
		return false;
	}
	return true;
	
}
void Tiger::Draw()
{
	m_skinModel.UpdateWorldMatrix(
		m_position,
		m_rotation,
		{ 1.0f, 1.0f, 1.0 });
	m_skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
