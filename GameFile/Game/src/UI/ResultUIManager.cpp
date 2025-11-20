/**
 * ResultUIManager.cpp
 *
 * リザルト中のUIを管理するクラス
 */
#include "stdafx.h"
#include "ResultUIManager.h"
#include "src/UI/ResultScreen.h"


namespace nsApp
{
    namespace nsUI
    {
        ResultUIManager* ResultUIManager::m_instance = nullptr;



        ResultUIManager::ResultUIManager()
        {
            m_resultScreen = NewGO<ResultScreen>(enGameObjectPriority_UI, "ResultScreen");
        }


        ResultUIManager::~ResultUIManager()
        {
            DeleteGO(m_resultScreen);
        }


        void ResultUIManager::Update()
        {           
        }
    }
}