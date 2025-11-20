/**
 * ResultScene.cpp
 *
 * リザルトシーン
 */
#include "stdafx.h"
#include "ResultScene.h"
#include "src/Scene/TitleScene.h"
#include "src/UI/ResultScreen.h"
#include "src/UI/LateResultScreen.h"
#include "src/UI/ResultUIManager.h"
#include "src/GameFlow/GameFlowManager.h"
#include "src/Core/SaveData.h"


namespace nsApp
{
    namespace nsScene
    {
        ResultScene::ResultScene()
        {
        }

        
        ResultScene::~ResultScene()
        {
            DeleteGO(m_resultScreen);
        }

       
        bool ResultScene::Start()
        {
            m_resultScreen = NewGO<nsUI::ResultScreen>(enGameObjectPriority_UI, "ResultScreen");
            m_resultScreen->Initialize(nsApp::nsCore::SaveData::Get().GetResultType());

            m_step = enType_Step1;

            return true;
        }

        
        void ResultScene::Update()
        {
            switch (m_step)
            {
                case nsApp::nsScene::ResultScene::enType_Step1:
                {
                    if (g_pad[0]->IsTrigger(enButtonA)) {
                        m_step = enType_Step2;
                        DeleteGO(m_resultScreen);
                        m_lateResultScreen = NewGO<nsUI::LateResultScreen>(enGameObjectPriority_UI, "LateResultScreen");
                    }

                    break;
                }
                
                case nsApp::nsScene::ResultScene::enType_Step2:
                {                        
                    if (g_pad[0]->IsTrigger(enButtonA)) {
                        m_step = enType_Step3;
                    }

                    break;
                }
                
                default:
                {
                    break;
                }                
            }
        }       


        bool ResultScene::RequestScene(uint32_t& id)
        {
            if (m_step == enType_Step3 && g_pad[0]->IsTrigger(enButtonA)) {
                DeleteGO(m_lateResultScreen);
                id = nsScene::TitleScene::ID();
                return true;
            }

            return false;
        }      
    }
}