#pragma once
#include "Physics/ICollider.h"

class BoxCollider : public ICollider
{
public:
	BoxCollider();
	~BoxCollider();

	void Create(const D3DXVECTOR3& halfSize);
	btCollisionShape* GetBody() override
	{
		return m_boxShape;
	}
private:
	btBoxShape*	m_boxShape = nullptr;
};

