/**
 * WallHPUI.cpp
 *
 * 防壁のHPのUIを表示するクラス
 */
#include "stdafx.h"
#include "WallHPUI.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI {


        WallHPUI::WallHPUI()
        {
        }


        WallHPUI::~WallHPUI()
        {
        }


        bool WallHPUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 470.0f, 0.0f);

            //HPバーの本体
            m_HPBar = m_uiCanvas->CreateUI<ImageUI>();
            m_HPBar->Initialize("Assets/UI/WallHP/HPBar.dds", 1100.0f, 58.0f, Vector3(-550.0f, 0.5f, 0.0f), Vector3::One, Quaternion::Identity);
            m_HPBar->SetPivot(Vector2(0.0f, 0.5f));
            m_HPBar->SetMulColor(Vector4::Red);

            //HPバーの背景
            auto* backImage = m_uiCanvas->CreateUI<ImageUI>();
            backImage->Initialize("Assets/UI/WallHP/HPBarBack.dds", 1122.0f, 71.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            m_uiCanvas->Update();

            return true;
        }


        void WallHPUI::Update()
        {
            m_uiCanvas->Update();

            /*if (m_maxDurability <= 0.0f) {
                return;
            }*/

            const float hp = static_cast<float>(m_durability);
            const float maxHp = static_cast<float>(m_maxDurability);

            const float wightScale = hp / maxHp;
            m_HPBar->SetSize(wightScale, 1.0f);

        }


        void WallHPUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}