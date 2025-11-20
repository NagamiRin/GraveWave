/**
 * CountdownUI.cpp
 *
 * カウントダウンUIの描画
 */
#include "stdafx.h"
#include "CountdownUI.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI
    {
        CountdownUI::CountdownUI()
        {
        }

        
        CountdownUI::~CountdownUI()
        {
        }

       
        bool CountdownUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(-900.0f, 200.0f, 0.0f);

            

            //メッセージの背景
            m_back = m_uiCanvas->CreateUI<ImageUI>();
            m_back->Initialize("Assets/UI/Countdown/Back.dds", 1000.0f, 100.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //カウントダウンの文字を生成
            m_count = m_uiCanvas->CreateUI<StringUI>();
            m_count->Initialize(L"次の襲撃まで：0 秒", 1.0f, Vector3::Zero, Vector4::Black, Vector2::Zero, 0.0f);

            m_uiCanvas->Update();
        
            return true;
        }

        
        void CountdownUI::Update()
        {
            //文字を更新
            wchar_t text[256];
            swprintf_s(text, 256, L"次の襲撃まで：%.1f　秒", m_currentSeconds);
            m_count->UpdateText(text);
           
            m_uiCanvas->Update();
        }

        
        void CountdownUI::Render(RenderContext& rc)
        {
            if(m_isDrawCount) m_uiCanvas->Render(rc);
        }
    }
}