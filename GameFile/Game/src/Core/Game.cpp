/**
 * Game.cpp
 *
 * ゲーム全体を管理するクラス
 */
#include "stdafx.h"
#include "Game.h"


namespace nsApp {
	namespace nsCore {

		Game::Game()
		{
			//当たり判定描画
			//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
		}


		Game::~Game()
		{
		}


		bool Game::Start()
		{
			return true;
		}


		void Game::Update()
		{
		}


		void Game::Render(RenderContext& rc)
		{
		}
	}
}
