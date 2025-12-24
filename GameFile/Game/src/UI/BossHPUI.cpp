/**
 * BossHPUI.cpp
 *
 * ボスのHPのUIを表示するクラス
 */
#include "stdafx.h"
#include "BossHPUI.h"
#include "src/UI/UIBase.h"


namespace {
    constexpr float YELLOW_RATE = 0.5f;
    constexpr float RAD_RATE = 0.2f;
    constexpr float BAR_WIDE_SIZE = 200.0f;
    constexpr float BAR_VERTICAL_SIZE = 7.0f;
}


namespace nsApp
{
    namespace nsUI {


        BossHPUI::BossHPUI()
        {
        }


        BossHPUI::~BossHPUI()
        {
        }


        bool BossHPUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(0.0f, 0.0f, 0.0f);
                        
            //HPバーの背景
            m_back = m_uiCanvas->CreateUI<ImageUI>();
            m_back->Initialize("Assets/UI/WallHP/NormalBack.dds", BAR_WIDE_SIZE, BAR_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //HPバーの本体
            m_HPBar = m_uiCanvas->CreateUI<ImageUI>();
            m_HPBar->Initialize("Assets/UI/WallHP/HPBar.dds", BAR_WIDE_SIZE, BAR_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);
            m_HPBar->SetPivot(Vector2(0.0f, 0.5f));
            m_HPBar->SetMulColor(Vector4(0.8f, 0.0f, 0.0f, 1.0f));

            m_uiCanvas->Update();

            return true;
        }


        void BossHPUI::Update()
        {
            //HPバーの位置を更新
            const float XAdjust = BAR_WIDE_SIZE / 2.0f;
            Vector2 Pos = Vector2::Zero;
            g_camera3D->CalcScreenPositionFromWorldPosition(Pos, Vector3(m_bossPosition.x, m_bossPosition.y + 220.0f, m_bossPosition.z));
            m_HPBar->SetPosition(Vector3(Pos.x - XAdjust, Pos.y, 0.0f));
            m_back->SetPosition(Vector3(Pos.x, Pos.y, 0.0f));

            //HPバーのサイズをかえる
            const float hp = static_cast<float>(m_HP);
            const float maxHp = static_cast<float>(m_maxHP);

            const float wightScale = hp / maxHp;
            m_HPBar->SetSize(wightScale, 1.0f);

            m_uiCanvas->Update();
        }


        void BossHPUI::Render(RenderContext& rc)
        {
            if(m_isAlive) m_uiCanvas->Render(rc);
        }
    }
}