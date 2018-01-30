#pragma once

#include "Physics/RigidBody.h"
#include "Physics/BoxCollider.h"
class Door
{
public:
	Door();
	~Door();
	void Init();
	void Update();
	void Draw();
private:
	SkinModelData	m_hashiraSkinModelData;
	SkinModel		m_hashiraSkinModel;
	RigidBody		m_hashiraRigidBody;
	BoxCollider		m_hashiraCollider;

	SkinModelData	m_doorSkinModelData;
	SkinModel		m_doorSkinModel;
	RigidBody		m_doorRigidBody;
	BoxCollider		m_doorCollider;

	btHingeConstraint* m_hingeConstraint = nullptr;
};

