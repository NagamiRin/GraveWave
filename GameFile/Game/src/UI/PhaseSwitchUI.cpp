///**
// * PhaseSwitchUI.h
// *
// * フェーズ切り替えのメッセージUI
// */
#include "stdafx.h"
#include "PhaseSwitchUI.h"
#include "src/UI/UIBase.h"
#include "src/GameFlow/GameFlowManager.h"

namespace 
{
    constexpr float DRAW_TIME = 3.0f;
}

namespace nsApp
{
    namespace nsUI
    {
        PhaseSwitchUI::PhaseSwitchUI()
        {
            m_drawTime = DRAW_TIME;
            m_currentTime = DRAW_TIME;

            //最初のフェーズを入れる
            m_currentPhase = enPreparation;
            m_changePhase = enPreparation;
        }

        
        PhaseSwitchUI::~PhaseSwitchUI()
        {
        }

       
        bool PhaseSwitchUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 330.0f, 0.0f);
            //背景画像
            m_back = m_uiCanvas->CreateUI<ImageUI>();
            m_back->Initialize("Assets/UI/SwitchPhase/Back.dds", 900.0f, 200.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            m_message = m_uiCanvas->CreateUI<ImageUI>();
            m_message->Initialize("Assets/UI/SwitchPhase/ROUND_DEFEND.DDS", 700.0f, 60.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            m_number = m_uiCanvas->CreateUI<NumberUI>();
            m_number->Initialize("Assets/UI/Numbers/Classic", 1, 30.0f, 60.0f, Vector3(-100.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
            m_number->SetColor(Vector4(1.0f, 0.902f, 0.588f, 1.0f));      

            return true;
        }

        
        void PhaseSwitchUI::Update()
        {
            if (m_currentTime <= m_drawTime)m_currentTime += g_gameTime->GetFrameDeltaTime();
            if (m_currentPhase == m_changePhase) return;

            //画像を変える
            if (m_changePhase == enBattle) {
                m_message->Initialize("Assets/UI/SwitchPhase/ROUND_DEFEND.DDS", 700.0f, 60.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
                m_number->NumberUpdate("Assets/UI/Numbers/Classic", m_waveNum, 30.0f, 60.0f);
                m_number->SetPosition(Vector3(-60.0f, 0.0f, 0.0f));
                m_number->SetColor(Vector4(1.0f, 0.902f, 0.588f, 1.0f));
            }
            else if (m_changePhase == enPreparation) {
                m_message->Initialize("Assets/UI/SwitchPhase/ROUND_COMPLETE.DDS", 700.0f, 60.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
                m_number->NumberUpdate("Assets/UI/Numbers/Classic", m_waveNum, 30.0f, 60.0f);
                m_number->SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
                m_number->SetColor(Vector4(0.471f, 0.667f, 0.882f, 1.0f));
            }

            m_currentPhase = m_changePhase;
            m_currentTime = 0.0f;

            m_uiCanvas->Update();
        }

        
        void PhaseSwitchUI::Render(RenderContext& rc)
        {
            if (m_currentTime >= m_drawTime) return;

            m_uiCanvas->Render(rc);
        }        
    }
}