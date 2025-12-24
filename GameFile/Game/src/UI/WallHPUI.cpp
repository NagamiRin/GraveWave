/**
 * WallHPUI.cpp
 *
 * 防壁のHPのUIを表示するクラス
 */
#include "stdafx.h"
#include "WallHPUI.h"
#include "src/UI/UIBase.h"


namespace {
    constexpr float YELLOW_RATE = 0.5f;
    constexpr float RAD_RATE = 0.2f;
    constexpr float NUMBER_WIDE_SIZE = 18.0f;
    constexpr float NUMBER_VERTICAL_SIZE = 32.0f;
}


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
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);
                        
            //HPバーの背景
            auto* backImage = m_uiCanvas->CreateUI<ImageUI>();
            backImage->Initialize("Assets/UI/WallHP/HPBarBack.dds", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //耐久度の％表示
            m_rate = m_uiCanvas->CreateUI<NumberUI>();
            m_rate->Initialize("Assets/UI/Numbers/Classic/", 0, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE, Vector3(60.0f, -425.0f, 0.0f), Vector3::One, Quaternion::Identity);
            m_rate->SetColor(Vector4(0.0f, 0.5f, 0.0f, 1.0f));

            //HPバーの本体
            m_HPBar = m_uiCanvas->CreateUI<ImageUI>();
            m_HPBar->Initialize("Assets/UI/WallHP/HPBar.dds", 645.0f, 28.0f, Vector3(-324.0f, -456.0f, 0.0f), Vector3::One, Quaternion::Identity);
            m_HPBar->SetPivot(Vector2(0.0f, 0.5f));
            m_HPBar->SetMulColor(Vector4(0.0f, 0.5f, 0.0f, 1.0f));

            m_uiCanvas->Update();

            return true;
        }


        void WallHPUI::Update()
        {
            //HPバーのサイズをかえる
            const float hp = static_cast<float>(m_durability);
            const float maxHp = static_cast<float>(m_maxDurability);

            const float wightScale = hp / maxHp;
            m_HPBar->SetSize(wightScale, 1.0f);

            //HPバーの色を変える
            const float rate = hp / maxHp;
            if (rate <= RAD_RATE)m_HPBar->SetMulColor(Vector4(0.7f, 0.2f, 0.2f, 1.0f));
            else if (rate <= YELLOW_RATE) m_HPBar->SetMulColor(Vector4(0.7f, 0.7f, 0.1f, 1.0f));

            //％表示をかえる
            m_rate->NumberUpdate("Assets/UI/Numbers/Classic/", static_cast<uint8_t>(rate * 100), NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE);
            m_rate->SetColor(Vector4(0.0f, 0.5f, 0.0f, 1.0f));

            m_uiCanvas->Update();
        }


        void WallHPUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}