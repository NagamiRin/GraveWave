/**
 * Crosshair.cpp
 *
 * クロスヘアの描画
 */
#include "stdafx.h"
#include "src/UI/Crosshair.h"


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
            m_crosshairImage.Init("Assets/UI/Crosshair.DDS", 100.0f, 100.0f);
            m_crosshairImage.Update();
            return true;
        }

        
        void Crosshair::Update()
        {
        }

        
        void Crosshair::Render(RenderContext& rc)
        {
			m_crosshairImage.Draw(rc);
        }
    }
}