/**
 * Game.cpp
 *
 * ゲーム全体を管理するクラス
 */
#include "stdafx.h"
#include "src/Core/Game.h"
#include "src/Actor/Player/Player.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/GameCamera.h"
#include "src/Core/BattleManager.h"


namespace nsApp {
	namespace nsCore {

		Game::Game()
		{
			// BattleMangerの生成
			nsApp::nsCore::BattleManager::CreateInstance();
			// BattleMangerのインスタンス取得
			m_battleManager = nsApp::nsCore::BattleManager::GetInstance();

			//当たり判定描画
			//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
		}


		Game::~Game()
		{
			// BattleMangerの削除
			nsApp::nsCore::BattleManager::DeleteInstance();
		}


		bool Game::Start()
		{
			/** @TODO: for test */
			for (int i = 0; i < 5; ++i)
			{
				auto* zombie = NewGO<nsApp::nsActor::nsEnemy::Zombie>(i);
				zombie->SetLocalPosition(Vector3(i * 20.0f, 0.0f, 0.0f));
			}

			return true;
		}


		void Game::Update()
		{
			// BattleManagerの更新処理
			m_battleManager->Update();
		}


		void Game::Render(RenderContext& rc)
		{
		}
	}
}
