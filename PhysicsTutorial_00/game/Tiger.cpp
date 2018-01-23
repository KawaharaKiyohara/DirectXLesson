#include "stdafx.h"
#include "Tiger.h"
#include "game.h"

namespace {
	//minからmaxまでの値を補間変数ｔで線形補完。
	float Lerp(float t, float min, float max)
	{
		return min * (1.0f - t) + max *  t;
	}
}
Tiger::Tiger(SkinModelData* skinModelData)
{
	//ライトの初期化。
	InitLight();

	//座標の初期化。
	InitPosition();
	m_skinModelData = skinModelData;
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetLight(&light);

	m_boxCollider.Create({ 0.5f, 0.7f, 1.0f });	//Boxコライダーを作る。
	//剛体を作る。
	RigidBodyInfo rbInfo;						//剛体の情報を作成。
	D3DXQuaternionIdentity(&m_rotation);
	rbInfo.pos = m_position;					//剛体の初期位置。
	rbInfo.rot = m_rotation;					//剛体の初期回転。
	rbInfo.mass = 1.0f;							//質量。
	rbInfo.localInertia = { 1.0f, 1.0f, 1.0f };	//慣性。
	rbInfo.collider = &m_boxCollider;
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加。
	game->GetPhysicsWorld()->AddRigidBody(&m_rigidBody);
}
Tiger::~Tiger()
{
	//剛体を物理ワールドから削除。
	game->GetPhysicsWorld()->RemoveRigidBody(&m_rigidBody);
}
void Tiger::InitPosition()
{
	//虎の初期位置をランダムに決定。
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
	//モーションステートを取得。
	btDefaultMotionState* motionState = m_rigidBody.GetMotionState();
	btTransform transform;
	motionState->getWorldTransform(transform);				//剛体のトランスフォームを取得。
	m_position = (D3DXVECTOR3)transform.getOrigin();		//座標を反映。
	m_rotation = (D3DXQUATERNION)transform.getRotation();	//回転を反映。
	
	m_timer++;
	if (m_timer == 1000) {
		//1000フレームで死亡する。
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
