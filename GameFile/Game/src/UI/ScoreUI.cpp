/**
 * ScoreUI.cpp
 *
 * スコアを計算、管理するクラス
 */
#include "stdafx.h"
#include "ScoreUI.h"
#include "src/UI/UIBase.h"


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
            m_uiCanvas->m_transform.m_localPosition = Vector3(700.0f, 450.0f, 0.0f);

            //文字UIを生成
            m_scoreUI = m_uiCanvas->CreateUI<StringUI>();
            m_scoreUI->Initialize(L"スコア：0", 1.0f, Vector3::Zero, Vector4::White, Vector2::Zero, 0.0f);

            return true;
        }


        void ScoreUI::Update()
        {
            wchar_t text[256];
            swprintf_s(text, 256, L"スコア：%d",uint16_t(m_score));
            m_scoreUI->UpdateText(text);

            m_uiCanvas->Update();
        }


        void ScoreUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}