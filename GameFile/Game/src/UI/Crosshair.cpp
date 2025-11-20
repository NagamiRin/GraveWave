/**
 * Crosshair.cpp
 *
 * クロスヘアの描画
 */
#include "stdafx.h"
#include "Crosshair.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI
    {
        Crosshair::Crosshair()
        {
        }

        
        Crosshair::~Crosshair()
        {
        }

       
        bool Crosshair::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;

            //クロスヘアUIを生成
            auto* crosshair = m_uiCanvas->CreateUI<ImageUI>();
            crosshair->Initialize("Assets/UI/Crosshair/Crosshair.DDS", 80.0f, 80.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

            return true;
        }

        
        void Crosshair::Update()
        {
            m_uiCanvas->Update();
        }

        
        void Crosshair::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}