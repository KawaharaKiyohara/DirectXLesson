#pragma once

#include "Physics/RigidBody.h"
#include "Physics/BoxCollider.h"

class Tiger
{
public:
	Tiger(SkinModelData* skinModelData);
	~Tiger();
	bool Update();
	void Draw();
private:
	void InitLight();
	void InitPosition();
private:
	Light light;
	SkinModel		m_skinModel;		//�X�L�����f��
	SkinModelData*	m_skinModelData;	//�X�L�����f���f�[�^�B
	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	RigidBody		m_rigidBody;		//���́B
	BoxCollider		m_boxCollider;		//�{�b�N�X�R���C�_�[�B
	int				m_timer=0;
};

