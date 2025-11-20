/**
 * IScene.cpp
 *
 * 各シーンの基底クラス
 */
#include "stdafx.h"
#include "IScene.h"


namespace nsApp
{
    namespace nsScene
    {
        IScene::IScene()
        {
        }

        
        IScene::~IScene()
        {
        }

       
        bool IScene::Start()
        {
            return true;
        }

        
        void IScene::Update()
        {
        }       
    }
}