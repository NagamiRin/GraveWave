/**
 * ShopUI.cpp
 *
 * ショップUIの描画
 */
#include "stdafx.h"
#include "ShopUI.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsUI
    {
        ShopUI::ShopUI()
        {
        }

        
        ShopUI::~ShopUI()
        {
        }

       
        bool ShopUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;          


            //todo for test
            m_isOpen = true;
            for (int i = 0; i < 3; ++i) {
                auto* canvas = m_uiCanvas->CreateUI<UICanvas>();
                canvas->m_transform.m_localPosition = Vector3(-200.0f + (200.0f * i), 0.0f, 0.0f);
                auto* back = canvas->CreateUI<ImageUI>();
                back->Initialize("Assets/UI/Shop/IconBack.dds", 200.0f, 200.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
                back->SetMulColor(Vector4::White);
                auto* icon = canvas->CreateUI<ImageUI>();
                icon->Initialize("Assets/UI/Numbers/Pop/1.dds", 20.0f, 20.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
                icon->SetMulColor(Vector4::Black);
				m_uiItemList.push_back(back);
            }


            m_uiCanvas->Update();
        
            return true;
        }

        
        void ShopUI::Update()
        {
            
           
            m_uiCanvas->Update();
        }

        
        void ShopUI::Render(RenderContext& rc)
        {
            if(m_isOpen) m_uiCanvas->Render(rc);
        }
    }
}