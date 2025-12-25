/**
 * ReloadingUI.cpp
 *
 * リロード時間UIの描画
 */
#include "stdafx.h"
#include "ReloadingUI.h"
#include "src/UI/UIBase.h"


namespace {
    constexpr float IMAGE_WIDE_SIZE = 300.0f;
    constexpr float IMAGE_VERTICAL_SIZE = 20.0f;
    constexpr float STRING_WIDE_SIZE = 200.0f;
    constexpr float STRING_VERTICAL_SIZE = 50.0f;
    constexpr float BLINK_TIME = 2.0f;
}


namespace nsApp
{
    namespace nsUI
    {
        ReloadingUI::ReloadingUI()
        {
        }

        
        ReloadingUI::~ReloadingUI()
        {
        }

       
        bool ReloadingUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, -70.0f, 0.0f);

            //バー
            m_bar = m_uiCanvas->CreateUI<ImageUI>();
            m_bar->Initialize("Assets/UI/Reloading/Bar.dds", IMAGE_WIDE_SIZE, IMAGE_VERTICAL_SIZE, Vector3(-IMAGE_WIDE_SIZE / 2, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
            m_bar->SetPivot(Vector2(0.0f, 0.5f));

            //リロードの文字
            m_string = m_uiCanvas->CreateUI<ImageUI>();
            m_string->Initialize("Assets/UI/Reloading/Reloading.dds", STRING_WIDE_SIZE, STRING_VERTICAL_SIZE, Vector3(0.0f, 50.0f, 0.0f), Vector3::One, Quaternion::Identity);

            return true;
        }

        
        void ReloadingUI::Update()
        {
            //バーの横幅を更新
            float t = m_currentTime / m_reloadTime;
            m_bar->SetSize(IMAGE_WIDE_SIZE * t / 300.0f, 1.0f);

            //Reloadingの文字を点滅させる
            m_currentBlinkTime += g_gameTime->GetFrameDeltaTime();
            float u = 0.0f;

            if (m_currentBlinkTime <= BLINK_TIME / 2) {
                u = m_currentBlinkTime / (BLINK_TIME / 2);
            }
            else {
                u = m_currentBlinkTime - (BLINK_TIME / 2) / (BLINK_TIME / 2);
                u = 1.0f - u;
            };

            m_string->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, u));

            if (m_currentBlinkTime >= BLINK_TIME) m_currentBlinkTime = 0.0f;
            m_uiCanvas->Update();
        }

        
        void ReloadingUI::Render(RenderContext& rc)
        {
            if (m_currentTime <= 0.0f) return;

            m_uiCanvas->Render(rc);
        }
    }
}