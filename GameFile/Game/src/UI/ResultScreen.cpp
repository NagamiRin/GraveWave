/**
 * ResultScreen.cpp
 *
 * リザルト画面の表示
 */
#include "stdafx.h"
#include "ResultScreen.h"
#include "src/UI/UIBase.h"
#include "src/Core/SaveData.h"


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
                path = "Assets/Image/GameOverScreen.DDS";
            }
            if (type == enResultType_Over) {
                path = "Assets/Image/GameOverScreen.DDS";
            }
            titleImage->Initialize(path.c_str(), 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
        }
    }
}