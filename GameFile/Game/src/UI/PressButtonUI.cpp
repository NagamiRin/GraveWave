/**
 * PressButtonUI.cpp
 *
 * PressButtonの文字列の表示
 */
#include "stdafx.h"
#include "PressButtonUI.h"
#include "src/UI/UIBase.h"


namespace {
    constexpr float WIDE_SIZE = 500.0f;
    constexpr float VERTICAL_SIZE = 80.0f;
    constexpr float BLINK_TIME = 2.0f;
}


namespace nsApp
{
    namespace nsUI
    {
        PressButtonUI::PressButtonUI()
        {
        }

        
        PressButtonUI::~PressButtonUI()
        {
        }

       
        bool PressButtonUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, -300.0f, 0.0f);

            //文字
            m_string = m_uiCanvas->CreateUI<ImageUI>();
            m_string->Initialize("Assets/UI/PressButton/PressAnyButton.dds", WIDE_SIZE, VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);

            return true;
        }

        
        void PressButtonUI::Update()
        {
            //文字を点滅させる
            m_currentTime += g_gameTime->GetFrameDeltaTime();
            float t = 0.0f;

            if (m_currentTime <= BLINK_TIME / 2) {
                t = m_currentTime / (BLINK_TIME / 2);
            }
            else {
                t = m_currentTime - (BLINK_TIME / 2) / (BLINK_TIME / 2);
                t = 1.0f - t;
            };

            m_string->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, t));

            if (m_currentTime >= BLINK_TIME) m_currentTime = 0.0f;


            m_uiCanvas->Update();
        }

        
        void PressButtonUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}