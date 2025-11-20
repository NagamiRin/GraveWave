/**
 * TitleUIManager.cpp
 *
 * タイトルシーンのUIを管理するクラス
 */
#include "stdafx.h"
#include "TitleUIManager.h"
#include "src/UI/TitleScreen.h"


namespace nsApp
{
    namespace nsUI
    {
        TitleUIManager* TitleUIManager::m_instance = nullptr;


        TitleUIManager::TitleUIManager()
        {
            m_titleScreen = NewGO<TitleScreen>(enGameObjectPriority_UI, "TitleScreen");
        }


        TitleUIManager::~TitleUIManager()
        {
            DeleteGO(m_titleScreen);
        }


        void TitleUIManager::Update()
        {
        }
    }
}