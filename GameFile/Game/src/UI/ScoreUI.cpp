/**
 * ScoreUI.cpp
 *
 * スコアを計算、管理するクラス
 */
#include "stdafx.h"
#include "ScoreUI.h"
#include "src/UI/UIBase.h"
#include "src/Battle/Inventory.h"


namespace {
    constexpr float NUMBER_WIDE_SIZE = 25.0f;
    constexpr float NUMBER_VERTICAL_SIZE = 40.0f;
    constexpr float ICON_WIDE_SIZE = 50.0f;
    constexpr float ICON_VERTICAL_SIZE = 50.0f;
}


namespace nsApp
{
    namespace nsUI {


        ScoreUI::ScoreUI()
        {            
        }


        ScoreUI::~ScoreUI()
        {
        }

        bool ScoreUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(800.0f, 470.0f, 0.0f);

            //背景
            auto* back = m_uiCanvas->CreateUI <ImageUI>();
            back->Initialize("Assets/UI/Money/Back.dds", 400.0f, 100.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            back->SetMulColor(Vector4(0.3f, 0.3f, 0.3f, 1.0f));

            //数列
            m_money = m_uiCanvas->CreateUI<NumberUI>();
            m_money->Initialize("Assets/UI/Numbers/Classic", 0, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE, Vector3(0.0f, -10.0f, 0.0f), Vector3::One, Quaternion::Identity);

            //お金のアイコン
            auto* icon = m_uiCanvas->CreateUI<ImageUI>();
            icon->Initialize("Assets/UI/Money/Money.dds", ICON_WIDE_SIZE, ICON_VERTICAL_SIZE, Vector3(-130.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);

            return true;
        }


        void ScoreUI::Update()
        {
            m_money->NumberUpdate("Assets/UI/Numbers/Classic", m_currentMoney, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE);

            m_uiCanvas->Update();
        }


        void ScoreUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}