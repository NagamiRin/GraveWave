/**
 * ResultScreen.cpp
 *
 * リザルト画面の表示
 */
#include "stdafx.h"
#include "ResultScreen.h"
#include "src/UI/UIBase.h"
#include "src/Core/SaveData.h"


namespace {
    constexpr float WIDE_SIZE = 400.0f;
    constexpr float VERTICAL_SIZE = 60.0f;
    constexpr float BLINK_TIME = 2.0f;
}


namespace nsApp
{
    namespace nsUI
    {
        ResultScreen::ResultScreen()
        {
        }

        
        ResultScreen::~ResultScreen()
        {
        }

       
        bool ResultScreen::Start()
        {
            // ここでは何もしない
            return true;
        }

        
        void ResultScreen::Update()
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

        
        void ResultScreen::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }


        void ResultScreen::Initialize(const EnResultType type)
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;

            //リザルトの画像を生成
            auto* titleImage = m_uiCanvas->CreateUI<ImageUI>();
            std::string path;
            if (type == enResultType_Clear) {
                path = "Assets/Image/GameClear.DDS";
            }
            if (type == enResultType_Over) {
                path = "Assets/Image/GameOver.DDS";
            }
            titleImage->Initialize(path.c_str(), 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //ReturnToTitleの文字
            m_string = m_uiCanvas->CreateUI<ImageUI>();
            m_string->Initialize("Assets/UI/Result/ReturnToTitle.dds", WIDE_SIZE, VERTICAL_SIZE, Vector3(0.0f, -300.0f, 0.0f), Vector3::One, Quaternion::Identity);
        }
    }
}