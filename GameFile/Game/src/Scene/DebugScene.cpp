/**
 * TitleScene.cpp
 *
 * タイトルシーン
 */
#include "stdafx.h"
#include "src/Scene/DebugScene.h"
#include "src/Scene/InGameScene.h"

#include "src/UI/PhaseSwitchUI.h"

namespace
{
    static nsApp::nsUI::PhaseSwitchUI* debugUI = nullptr;
}


namespace nsApp
{
    namespace nsScene
    {
        DebugScene::DebugScene()
        {
        }

        
        DebugScene::~DebugScene()
        {
        }

       
        bool DebugScene::Start()
        {
            debugUI = NewGO<nsApp::nsUI::PhaseSwitchUI>(0, "PhaseSwitchUI");

            return true;
        }

        
        void DebugScene::Update()
        {
            static int phase = 0;
            if (g_pad[0]->IsTrigger(enButtonB)) {
                phase++;
            }
            debugUI->ChangePhase(phase);
        }       


        bool DebugScene::RequestScene(uint32_t& id)
        {
            return false;
        }
    }
}