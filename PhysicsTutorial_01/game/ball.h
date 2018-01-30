#pragma once

#include "Physics/SphereCollider.h"

class Ball
{
public:
	Ball();
	~Ball();
	void Init(const D3DXVECTOR3& initPos, float mass);
	void Update();
	void Draw();
	RigidBody& GetRigiBody()
	{
		return m_rigidBody;
	}
private:
	SkinModelData	m_skinModelData;
	SkinModel		m_skinModel;
	D3DXVECTOR3		m_position = D3DXVECTOR3(10.0f, 5.0f, 10.0f);
	D3DXQUATERNION	m_rotation = D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 1.0f );
	RigidBody		m_rigidBody;
	SphereCollider	m_sphereCollider;
};

