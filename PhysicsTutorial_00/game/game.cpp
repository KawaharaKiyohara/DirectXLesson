/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"


/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	//物理ワールドを初期化。
	physicsWorld.Init();
	//カメラ初期化。
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 10.0f, 10.5f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 8.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.SetAspect(1280.0f/720.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	//プレイヤーを初期化。
	player.Init();
	//マップを初期化。
	map.Init();
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	player.Update();
	//プレイヤー追従カメラ。
	D3DXVECTOR3 targetPos = player.GetPosition();
	targetPos.y += 2.0f;
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);
	camera.Update();
	map.Update();
	tigerCreater.Update();
	physicsWorld.Update();
}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	player.Draw();
	map.Draw();
	tigerCreater.Draw();
}
