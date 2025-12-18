/**
 * CountdownUI.cpp
 *
 * カウントダウンUIの描画
 */
#include "stdafx.h"
#include "CountdownUI.h"
#include "src/UI/UIBase.h"


namespace {
    constexpr float NEEDLE_WIDE_SIZE = 15.0f;
    constexpr float NEEDLE_VERTICAL_SIZE = 50.0f;
    constexpr float BLINK_RAITO = 0.25f;
    constexpr float BLINK_SPEED = 3.0f;
}


namespace nsApp
{
    namespace nsUI
    {
        CountdownUI::CountdownUI()
        {
        }

        
        CountdownUI::~CountdownUI()
        {
        }

       
        bool CountdownUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 350.0f, 0.0f);            

            //時計
            m_clock = m_uiCanvas->CreateUI<ImageUI>();
            m_clock->Initialize("Assets/UI/Countdown/Clock.dds", 200.0f, 200.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //カウントダウンの文字を生成
            /*m_count = m_uiCanvas->CreateUI<NumberUI>();
            m_count->Initialize("Assets/UI/Numbers/Classic", 0, 30.0f, 30.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);*/

            //時計の針
            m_hands = m_uiCanvas->CreateUI<ImageUI>();
            m_hands->Initialize("Assets/UI/CountDown/Needle.dds", NEEDLE_WIDE_SIZE, NEEDLE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);
            m_hands->SetPivot(Vector2(0.5f, 0.1f));

            m_uiCanvas->Update();
        
            return true;
        }

        
        void CountdownUI::Update()
        {
            if (m_countTime == 0.0f) return;

            //秒数を更新
            //m_count->NumberUpdate("Assets/UI/Numbers/Classic", m_currentSeconds, 50.0f, 50.0f);

            //針の向きを更新
            const float elapsedRaito = (m_countTime - m_currentSeconds) / m_countTime;
            float rotAngle = elapsedRaito * 360.0f;
            rotAngle = 360.0f - rotAngle;
            m_handsRot.SetRotationDegZ(rotAngle);
            m_hands->SetRotation(m_handsRot);

            //時間が迫ったら赤く点滅させる
            if (m_currentSeconds <= m_countTime * BLINK_RAITO) {
                m_blinkTime += g_gameTime->GetFrameDeltaTime();
                float t = std::abs(std::sin(m_blinkTime * BLINK_SPEED));

                m_clock->SetMulColor(Vector4(1.0f, t, t, 1.0f));
            } 
            else {
                m_clock->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
                m_blinkTime = 0.0f;
            }
            

            m_uiCanvas->Update();
        }

        
        void CountdownUI::Render(RenderContext& rc)
        {
            if(m_isDrawCount) m_uiCanvas->Render(rc);
        }
    }
}