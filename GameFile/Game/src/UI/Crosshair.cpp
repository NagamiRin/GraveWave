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
            m_crosshairImage = m_uiCanvas->CreateUI<ImageUI>();
            m_crosshairImage->Initialize("Assets/UI/Crosshair/Crosshair.DDS", 40.0f, 40.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            m_crosshairImage->SetMulColor(Vector4::Black);

            //ヒットエフェクトを生成
            m_hitEffect = m_uiCanvas->CreateUI<ImageUI>();
            m_hitEffect->Initialize("Assets/UI/Crosshair/HitEffect.dds", 50.0f, 50.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            m_hitEffect->SetMulColor(Vector4::Black);
            m_hitEffect->SetIsDraw(false);

            return true;
        }

        
        void Crosshair::Update()
        {
            //照準が敵にあっているなら色を変える
            m_crosshairImage->SetMulColor(m_isHit ? Vector4::Red : Vector4::Black);

            m_currentTime -= g_gameTime->GetFrameDeltaTime();
            if (m_currentTime <= 0.0f)m_currentTime = 0.0f;

            if (m_isHit) {
                m_hitEffect->SetIsDraw(true);
                m_currentTime = 0.5f;
            }
            else if (!m_isHit && m_currentTime == 0.0f) {
                m_hitEffect->SetIsDraw(false);
            }

            m_uiCanvas->Update();
        }

        
        void Crosshair::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}