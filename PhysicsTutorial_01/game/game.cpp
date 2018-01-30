/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"
#include "ball.h"

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
	for (auto ball : balls) {
		delete ball;
	}
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
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
	//�h�A���������B
	door.Init();
	//�{�[�����쐬�B
	InitBalls();
}
void Game::InitBalls()
{
	D3DXVECTOR3 initPos = { 10.0f, 5.0f, 10.0f };
	for (int x = 0; x < 10; x++) {
		Ball* prevBall = nullptr;
		for (int y = 0; y < 10; y++) {
			Ball* ball = new Ball();
			if (y == 0) {
				//�ÓI����
				ball->Init(initPos, 0.0f);
			}
			else {
				ball->Init(initPos, 0.5f);
			}
			balls.push_back(ball);
			if (prevBall != nullptr) {
				btPoint2PointConstraint* constraint = new btPoint2PointConstraint(
					*prevBall->GetRigiBody().GetBody(),
					*ball->GetRigiBody().GetBody(),
					{ 0.0f, -0.1f, 0.0f },
					{ 0.0f, 0.1f, 0.0f }
				);
				game->GetPhysicsWorld()->GetDynamicWorld()->addConstraint(constraint);
			}
			prevBall = ball;
			initPos.y -= 0.1f;
		}

		initPos.x += 0.3f;
		initPos.y = 5.0f;
	}
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
	door.Update();
	physicsWorld.Update();
	for (auto ball : balls) {
		ball->Update();
	}
}
/*!
 * @brief	�`��B
 */
void Game::Render()
{
	player.Draw();
	map.Draw();
	door.Draw();
	for (auto ball : balls) {
		ball->Draw();
	}
}
