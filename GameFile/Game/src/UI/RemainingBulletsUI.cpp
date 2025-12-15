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
    constexpr float canvasWideSize = 300.0f;
    constexpr float canvasVerticalSize = 110.0f;
    constexpr float IconWideSize = 250.0f;
    constexpr float IconVerticalSize = 60.0f;
}

namespace nsApp
{
    namespace nsUI
    {
        RemainingBulletsUI::RemainingBulletsUI()
        {
            m_changeGunName = "GZ75";
        }

        
        RemainingBulletsUI::~RemainingBulletsUI()
        {
        }

       
        bool RemainingBulletsUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(800.0f, -470.0f, 0.0f);

            //残弾数UIを生成
            //背景
            auto* backImage = m_uiCanvas->CreateUI<ImageUI>();
            backImage->Initialize("Assets/UI/RemainingBulletsUI/Back.DDS", canvasWideSize, canvasVerticalSize, Vector3::Zero, Vector3::One, Quaternion::Identity);
            backImage->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.3f));

            //残弾数の文字列
            m_ammoUI = m_uiCanvas->CreateUI<NumberUI>();
            m_ammoUI->Initialize("Assets/UI/Numbers/Classic", 1, 30.0f, 50.0f, Vector3(-20.0f, 80.0f, 0.0f), Vector3::One, Quaternion::Identity);
            m_ammoUI->SetColor(Vector4::White);

            //間の/
            ImageUI* slash = m_uiCanvas->CreateUI<ImageUI>();
            slash->Initialize("Assets/UI/ItemIcon/slash.dds", 15.0f, 35.0f, Vector3(40.0f, 75.0f, 0.0f), Vector3::One, Quaternion::Identity);


            //予備弾数の文字列
            m_spareAmmoUI = m_uiCanvas->CreateUI<NumberUI>();
            m_spareAmmoUI->Initialize("Assets/UI/Numbers/Classic", 10, 15.0f, 25.0f, Vector3(80.0f, 75.0f, 0.0f), Vector3::One, Quaternion::Identity);

            //銃のアイコン
            m_gunIcon = m_uiCanvas->CreateUI<ImageUI>();
            m_gunIcon->Initialize("Assets/UI/ItemIcon/GZ75.dds", IconWideSize, IconVerticalSize, Vector3::Zero, Vector3::One, Quaternion::Identity);

            return true;
        }

        
        void RemainingBulletsUI::Update()
        {
            if (m_gunName != m_changeGunName) {
                //銃アイコンの更新
                const std::string path = "Assets/UI/ItemIcon/" + m_changeGunName + ".dds";
                m_gunIcon->Initialize(path.c_str(), IconWideSize, IconVerticalSize, Vector3::Zero, Vector3::One, Quaternion::Identity);
                m_gunName = m_changeGunName;
            }

            //残弾数の更新
            m_ammoUI->NumberUpdate("Assets/UI/Numbers/Classic", m_remainingAmmo, 30.0f, 50.0f);

            //todo 予備弾の更新をしようね

            m_uiCanvas->Update();
        }

        
        void RemainingBulletsUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}