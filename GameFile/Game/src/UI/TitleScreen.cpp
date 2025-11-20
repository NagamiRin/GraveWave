/**
 * TitleScreen.cpp
 *
 * タイトル画面の表示
 */
#include "stdafx.h"
#include "TitleScreen.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI
    {
        TitleScreen::TitleScreen()
        {
        }

        
        TitleScreen::~TitleScreen()
        {
        }

       
        bool TitleScreen::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;

            //クロスヘアUIを生成
            auto* titleImage = m_uiCanvas->CreateUI<ImageUI>();
            titleImage->Initialize("Assets/Image/Title.DDS", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            return true;
        }

        
        void TitleScreen::Update()
        {
            m_uiCanvas->Update();
        }

        
        void TitleScreen::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}