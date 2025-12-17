/**
 * TitleUIManager.cpp
 *
 * タイトルシーンのUIを管理するクラス
 */
#include "stdafx.h"
#include "TitleUIManager.h"
#include "src/UI/TitleScreen.h"
#include "src/UI/PressButtonUI.h"


namespace nsApp
{
    namespace nsUI
    {
        TitleUIManager* TitleUIManager::m_instance = nullptr;


        TitleUIManager::TitleUIManager()
        {
            m_titleScreen = NewGO<TitleScreen>(enGameObjectPriority_UI, "TitleScreen");
            m_pressButton = NewGO<PressButtonUI>(enGameObjectPriority_UI, "PressButton");
        }


        TitleUIManager::~TitleUIManager()
        {
            DeleteGO(m_titleScreen);
            DeleteGO(m_pressButton);
        }


        void TitleUIManager::Update()
        {
        }
    }
}