/**
 * BattleManager.cpp
 *
 * 戦闘全体を管理するクラス
 */
#include "stdafx.h"
#include "src/Core/BattleManager.h"
#include "src/Collision/CollisionManager.h"
#include "src/GameCamera.h"
#include "src/Actor/Player/Player.h"
#include "src/UI/Crosshair.h"


namespace nsApp
{
    namespace nsCore {

        BattleManager* BattleManager::m_instance = nullptr;


        BattleManager::BattleManager()
        {
            BattleManager::GetInstance();

            CollisionHitManager::Create();



            //ゲームカメラを生成
            m_camera = NewGO<nsApp::GameCamera>(enGameObjectPriority_Camera, "GameCamera");
            //プレイヤーを生成
            m_player = NewGO<nsApp::nsActor::nsPlayer::Player>(0, "Player");
			//十字マークを生成
			NewGO<nsApp::nsUI::Crosshair>(0, "Crosshair");
        }


        BattleManager::~BattleManager()
        {
            CollisionHitManager::Delete();
        }


        void BattleManager::Update()
        {
            UpdateCameraForPlayer();
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