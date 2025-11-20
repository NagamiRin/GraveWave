/**
 * LateResultScreen.cpp
 *
 * 2つめのリザルト画面の表示
 */
#include "stdafx.h"
#include "LateResultScreen.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI
    {
        LateResultScreen::LateResultScreen()
        {
        }

        
        LateResultScreen::~LateResultScreen()
        {
        }

       
        bool LateResultScreen::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;

            m_scoreUI = m_uiCanvas->CreateUI<StringUI>();
            m_scoreUI->Initialize(L"スコア：0", 1.0f, Vector3::Zero, Vector4::White, Vector2::Zero, 0.0f);

            //リザルトの画像を生成
            auto* titleImage = m_uiCanvas->CreateUI<ImageUI>();
            titleImage->Initialize("Assets/Image/GameOverScreen.DDS", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            return true;
        }

        
        void LateResultScreen::Update()
        {
            m_uiCanvas->Update();
        }

        
        void LateResultScreen::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }       
    }
}