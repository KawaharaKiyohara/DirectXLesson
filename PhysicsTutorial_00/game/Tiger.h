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
	SkinModel		m_skinModel;		//スキンモデル
	SkinModelData*	m_skinModelData;	//スキンモデルデータ。
	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	RigidBody		m_rigidBody;		//剛体。
	BoxCollider		m_boxCollider;		//ボックスコライダー。
	int				m_timer=0;
};

