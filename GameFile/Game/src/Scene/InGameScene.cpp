/**
 * InGameScene.cpp
 *
 * インゲームシーン
 */
#include "stdafx.h"
#include "InGameScene.h"
#include "src/Scene/ResultScene.h"
#include "src/UI/InGameUIManager.h"
#include "src/Core/BattleManager.h"
#include "src/Core/SaveData.h"


namespace nsApp
{
    namespace nsScene
    {
        InGameScene::InGameScene()
        {
            nsCore::BattleManager::CreateInstance();
            nsUI::InGameUIManager::CreateInstance();
        }

        
        InGameScene::~InGameScene()
        {
            nsCore::BattleManager::DeleteInstance();
            nsUI::InGameUIManager::DeleteInstance();
        }

       
        bool InGameScene::Start()
        {
            //スカイキューブを生成
            SkyCube* skyCube = NewGO<SkyCube>(enGameObjectPriority_SkyCube, "SkyCube");
            skyCube->SetType(enSkyCubeType_Sunset);
            skyCube->SetScale(200.0f);
            return true;
        }

        
        void InGameScene::Update()
        {
            nsCore::BattleManager::GetInstance()->Update();
            nsUI::InGameUIManager::GetInstance()->Update();

            // ここでゲーム終了の状態を渡す
            if (nsCore::BattleManager::GetInstance()->IsBattleFinish()) {
                if (nsCore::BattleManager::GetInstance()->IsBattleWin()) {
                    nsApp::nsCore::SaveData::Get().SetResultType(enResultType_Clear);
                } 
                if (nsCore::BattleManager::GetInstance()->IsBattleLose()) {
                    nsApp::nsCore::SaveData::Get().SetResultType(enResultType_Over);
                }
            }
        }


        bool InGameScene::RequestScene(uint32_t& id)
        {
            if (nsCore::BattleManager::GetInstance()->IsBattleFinish()) {
                id = nsScene::ResultScene::ID();
                return true;
            }

            return false;
        }
    }
}