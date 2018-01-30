/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "Player.h"
#include "Map.h"
#include "Physics/Physics.h"
#include "ball.h"
#include "Door.h"

/*!
 * @brief	ゲームクラス。
 */
class Game{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	Game();
	/*!
	 * @brief	デストラクタ。
	 */
	~Game();
	/*!
	 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
	 */
	void Start();
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	描画。
	 */
	void Render();
	//ゲームカメラのインスタンスを取得。
	Camera* GetCamera()
	{
		return &camera;
	}
	//物理ワールドの取得。
	PhysicsWorld* GetPhysicsWorld()
	{
		return &physicsWorld;
	}
	//ライトを取得。
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