/**
 * LateResultScreen.cpp
 *
 * 2つめのリザルト画面の表示
 */
#include "stdafx.h"
#include "LateResultScreen.h"
#include "src/UI/UIBase.h"
#include "src/Core/SaveData.h"


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

            //リザルトの画像を生成
            auto* titleImage = m_uiCanvas->CreateUI<ImageUI>();
            titleImage->Initialize("Assets/Image/GameOverScreen.DDS", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //最終スコアを表示
            auto* finalScore = m_uiCanvas->CreateUI<NumberUI>();
            finalScore->Initialize("Assets/UI/Numbers", nsCore::SaveData::Get().GetScore(), 20.0f, 45.0f, Vector3(-900.0f, 150.0f, 0.0f), Vector3::One, Quaternion::Identity);
            finalScore->SetColor(Vector4::Black);

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