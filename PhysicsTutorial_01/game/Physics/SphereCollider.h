#pragma once
#include "Physics/ICollider.h"


class SphereCollider : public ICollider
{
public:
	SphereCollider();
	~SphereCollider();
	void Create(float radius);
	btCollisionShape* GetBody() override
	{
		return m_sphereShape;
	}
private:
	btSphereShape* m_sphereShape = nullptr;
};

