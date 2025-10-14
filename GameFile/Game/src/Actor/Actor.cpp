/**
 * Actor.cpp
 *
 * ゲームオブジェクトのベース
 */
#include "stdafx.h"
#include "src/Actor/Actor.h"


namespace nsApp
{
    namespace nsActor
    {
        Actor::Actor()
        {
        }

        
        Actor::~Actor()
        {
        }

       
        bool Actor::Start()
        {
            return true;
        }

        
        void Actor::Update()
        {
        }

        
        void Actor::Render(RenderContext& rc)
        {
        }
    }
}