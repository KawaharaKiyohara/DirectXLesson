#include "stdafx.h"
#include "BoxCollider.h"


BoxCollider::BoxCollider()
{
}


BoxCollider::~BoxCollider()
{
	delete m_boxShape;
}

void BoxCollider::Create(const D3DXVECTOR3& halfSize)
{
	btVector3 btHalfSize;
	btHalfSize.setX( halfSize.x );
	btHalfSize.setY( halfSize.y );
	btHalfSize.setZ( halfSize.z );

	m_boxShape = new btBoxShape(btHalfSize);
}