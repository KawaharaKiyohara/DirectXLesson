/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"


/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	//�������[���h���������B
	physicsWorld.Init();
	//�J�����������B
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 10.0f, 10.5f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 8.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.SetAspect(1280.0f/720.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	//�v���C���[���������B
	player.Init();
	//�}�b�v���������B
	map.Init();
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	player.Update();
	//�v���C���[�Ǐ]�J�����B
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
 * @brief	�`��B
 */
void Game::Render()
{
	player.Draw();
	map.Draw();
	tigerCreater.Draw();
}
