/**
 * RemainingBulletsUI.cpp
 *
 * クロスヘアの描画
 */
#include "stdafx.h"
#include "RemainingBulletsUI.h"
#include "src/UI/UIBase.h"


namespace
{
    constexpr float canvasWideSize = 548.0f;
}

namespace nsApp
{
    namespace nsUI
    {
        RemainingBulletsUI::RemainingBulletsUI()
        {
        }

        
        RemainingBulletsUI::~RemainingBulletsUI()
        {
        }

       
        bool RemainingBulletsUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(700.0f, -450.0f, 0.0f);

            //残弾数UIを生成
            //背景
            auto* backImage = m_uiCanvas->CreateUI<ImageUI>();
            backImage->Initialize("Assets/UI/RemainingBulletsUI/Back.DDS", canvasWideSize, 219.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //残弾数の文字列
            m_ammoUI = m_uiCanvas->CreateUI<NumberUI>();
            m_ammoUI->Initialize("Assets/UI/Numbers", 1, 30.0f, 50.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            m_ammoUI->SetColor(Vector4::White);

            return true;
        }

        
        void RemainingBulletsUI::Update()
        {
            m_ammoUI->NumberUpdate("Assets/UI/Numbers", m_remainingAmmo, 30.0f, 50.0f);

            if (m_bulletsIconList.size() != m_maxAmmo) {
                /*if (m_bulletsIconList.size() > m_maxAmmo)m_bulletsIconList.pop_back();
                if (m_bulletsIconList.size() > m_maxAmmo)m_bulletsIconList.pop_back();*/
            }

            m_uiCanvas->Update();
        }

        
        void RemainingBulletsUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }


        void RemainingBulletsUI::DecidePlace()
        {
            constexpr float maxWideSize = 50.0f;
            constexpr float verticalRatio = 2.0f;

            //弾アイコンを横に並べる

        }
    }
}