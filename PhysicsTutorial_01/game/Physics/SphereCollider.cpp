#include "stdafx.h"
#include "SphereCollider.h"


SphereCollider::SphereCollider()
{
}


SphereCollider::~SphereCollider()
{
}
void SphereCollider::Create(float radius)
{
	m_sphereShape = new btSphereShape(radius);
}