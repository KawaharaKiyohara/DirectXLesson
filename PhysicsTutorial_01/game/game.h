/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "Player.h"
#include "Map.h"
#include "Physics/Physics.h"
#include "ball.h"
#include "Door.h"

/*!
 * @brief	�Q�[���N���X�B
 */
class Game{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Game();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	 */
	void Start();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Render();
	//�Q�[���J�����̃C���X�^���X���擾�B
	Camera* GetCamera()
	{
		return &camera;
	}
	//�������[���h�̎擾�B
	PhysicsWorld* GetPhysicsWorld()
	{
		return &physicsWorld;
	}
	//���C�g���擾�B
	Light& GetLight()
	{
		return light;
	}
private:
	void InitBalls();
private:
	D3DXVECTOR3 toCameraPos;
	Camera camera;
	Player player;
	Map map;
	Door door;
	PhysicsWorld physicsWorld;
	std::vector<Ball*> balls;
	std::vector<btPoint2PointConstraint*>	pointToPointConstraint;	
	Light light;
};

extern Game* game;