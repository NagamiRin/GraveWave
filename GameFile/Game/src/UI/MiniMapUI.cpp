/**
 * MiniMapUI.cpp
 *
 * カウントダウンUIの描画
 */
#include "stdafx.h"
#include "MiniMapUI.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI
    {
        MiniMapUI::MiniMapUI()
        {
        }

        
        MiniMapUI::~MiniMapUI()
        {
        }

       
        bool MiniMapUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(900.0f, 200.0f, 0.0f);
            
            //ミニマップの背景
            ImageUI* back = m_uiCanvas->CreateUI<ImageUI>();
            back->Initialize("Assets/UI/MiniMapUI/Back.dds", 100.0f, 100.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //防壁のアイコン
            back = m_uiCanvas->CreateUI<ImageUI>();
            back->Initialize("Assets/UI/WallIcon/Back.dds", 100.0f, 100.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            m_uiCanvas->Update();
        
            return true;
        }

        
        void MiniMapUI::Update()
        {
            
            m_uiCanvas->Update();
        }

        
        void MiniMapUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}