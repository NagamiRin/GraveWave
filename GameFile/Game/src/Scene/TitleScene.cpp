/**
 * TitleScene.cpp
 *
 * タイトルシーン
 */
#include "stdafx.h"
#include "src/Scene/TitleScene.h"
#include "src/Scene/InGameScene.h"
#include "src/UI/TitleUIManager.h"


namespace nsApp
{
    namespace nsScene
    {
        TitleScene::TitleScene()
        {
            nsUI::TitleUIManager::CreateInstance();
        }

        
        TitleScene::~TitleScene()
        {
            nsUI::TitleUIManager::DeleteInstance();
        }

       
        bool TitleScene::Start()
        {
            return true;
        }

        
        void TitleScene::Update()
        {
            nsUI::TitleUIManager::GetInstance()->Update();
        }       


        bool TitleScene::RequestScene(uint32_t& id)
        {
            if (g_pad[0]->IsTrigger(enButtonA)) {
                id = InGameScene::ID();
                return true;
            }

            return false;
        }
    }
}