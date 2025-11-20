/**
 * RemainingEnemyUI.cpp
 *
 * スコアを計算、管理するクラス
 */
#include "stdafx.h"
#include "RemainingEnemyUI.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI {


        RemainingEnemyUI::RemainingEnemyUI()
        {            
        }


        RemainingEnemyUI::~RemainingEnemyUI()
        {
        }

        bool RemainingEnemyUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(-900.0f, 450.0f, 0.0f);

            //文字UIを生成
            m_enemyCountUI = m_uiCanvas->CreateUI<StringUI>();
            m_enemyCountUI->Initialize(L"残り：0 体", 1.0f, Vector3::Zero, Vector4::White, Vector2::Zero, 0.0f);

            return true;
        }


        void RemainingEnemyUI::Update()
        {
            wchar_t text[256];
            swprintf_s(text, 256, L"残り：%d 体",uint8_t(m_enemyCount));
            m_enemyCountUI->UpdateText(text);

            m_uiCanvas->Update();
        }


        void RemainingEnemyUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}