/**
 * LoadingScreen.cpp
 *
 * ロード画面の表示
 */
#include "stdafx.h"
#include "LoadingScreen.h"
#include "src/UI/UIBase.h"


namespace nsApp
{
    namespace nsScene
    {
        LoadingScreen::LoadingScreen()
        {
        }

        
        LoadingScreen::~LoadingScreen()
        {
        }

       
        bool LoadingScreen::Start()
        {
            m_loadingImage.Init("Assets/Image/Loading.dds", 1920.0f, 1080.0f);

            return true;
        }

        
        void LoadingScreen::Update()
        {
        }

        
        void LoadingScreen::Render(RenderContext& rc)
        {
            if(m_isDraw) m_loadingImage.Draw(rc);
        }
    }
}