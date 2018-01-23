#include "stdafx.h"
#include "Player.h"
#include "game.h"

Player::Player()
{
}


Player::~Player()
{
	//ハンズオン 1-3
	if (normalMap != NULL) {
		//normalMapがNULLじゃないならロードされているので開放する。
		normalMap->Release();
	}
}
void Player::Init()
{
	
		//モデルをロード。
	modelData.LoadModelData("Assets/model/Unity.X", &animation);

	model.Init(&modelData);
	model.SetLight(game->GetDefaultLight());

	//ハンズオン 1-2
	D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Assets/model/utc_nomal.tga",
		&normalMap
	);
	//モデルに法線マップを設定。
	model.SetNormalMap(normalMap);
	
	animation.PlayAnimation(0);
}
void Player::Update()
{
	/*if (GetAsyncKeyState('A')) {
		//法線マップのオフ
		model.SetNormalMap(NULL);
	}
	else if (GetAsyncKeyState('S')) {
		//法線マップのオン
		model.SetNormalMap(normalMap);
	}*/
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}
void Player::Render()
{
	Camera* cam = game->GetCamera();
	model.Draw(&cam->GetViewMatrix(), &cam->GetProjectionMatrix());
}