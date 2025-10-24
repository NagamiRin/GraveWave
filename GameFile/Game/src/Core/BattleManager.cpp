/**
 * BattleManager.cpp
 *
 * 戦闘全体を管理するクラス
 */
#include "stdafx.h"
#include "BattleManager.h"
#include "src/Actor/BackGround/BackGround.h"
#include "src/Actor/Enemy/EnemySpawner.h"
#include "src/Actor/Player/Player.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ParameterManager.h"
#include "src/GameCamera.h"
#include "src/UI/Crosshair.h"


namespace nsApp
{
    namespace nsCore {

        BattleManager* BattleManager::m_instance = nullptr;


        BattleManager::BattleManager()
        {
            BattleManager::GetInstance();

            CollisionHitManager::Create();

            //パラメーター読み込み
            ParameterManager::Get().LoadParameter<MasterBattleParameter>("Assets/Parameter/BattleParameter.json", [](const nlohmann::json& j, MasterBattleParameter& p)
                {
                    p.m_maxEnemyNum = j["MaxEnemyNum"].get<uint8_t>();
                    p.m_baseSpawnTime = j["BaseSpawnTime"].get<float>();
                    p.m_spawnPositionX = j["SpawnPositionX"].get<float>();
                    p.m_spawnPositionY = j["SpawnPositionY"].get<float>();
                    p.m_spawnPositionZ = j["SpawnPositionZ"].get<float>();
                });

            auto* parameter = ParameterManager::Get().GetParameter<MasterBattleParameter>();


            //背景を生成
            m_backGround = NewGO<nsApp::nsActor::nsBackGround::BackGround>(enGameObjectPriority_BackGround, "BackGround");
            //エネミーのスポナーを生成
            m_enemySpawner = std::make_unique<nsApp::nsActor::nsEnemy::EnemySpawner>(parameter->m_maxEnemyNum, parameter->m_baseSpawnTime, Vector3(parameter->m_spawnPositionX, parameter->m_spawnPositionY, parameter->m_spawnPositionZ));
            //ゲームカメラを生成
            m_camera = NewGO<nsApp::GameCamera>(enGameObjectPriority_Camera, "GameCamera");
            //プレイヤーを生成
            m_player = NewGO<nsApp::nsActor::nsPlayer::Player>(enGameObjectPriority_Player, "Player");
			//十字マークを生成
			NewGO<nsApp::nsUI::Crosshair>(enGameObjectPriority_UI, "Crosshair");
        }


        BattleManager::~BattleManager()
        {
            CollisionHitManager::Delete();

            ParameterManager::Get().UnloadParameter<MasterBattleParameter>();
        }


        void BattleManager::Update()
        {
            CollisionHitManager::Get().Update();

            UpdateCameraForPlayer();

            m_enemySpawner->Create();
            m_enemySpawner->CountTime();
        }


        void BattleManager::DeleteZombie(nsApp::nsActor::nsEnemy::Zombie* zombie)
        {
            m_enemySpawner->Delete(zombie); 
        }


        void BattleManager::UpdateCameraForPlayer()
        {
            //カメラ座標を設定
            m_camera->SetCameraPos(m_player->GetPosition());
            //カメラの向きを設定
            m_camera->SetCameraDir(m_player->GetDirection());
        }
    }
}