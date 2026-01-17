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
            //モデルの更新
            m_model.SetPosition(m_transform.m_localPosition);
            m_model.SetRotation(m_transform.m_localRotation);
            m_model.SetScale(m_transform.m_localScale);
            m_model.Update();       
        }

        
        void Actor::Render(RenderContext& rc)
        {
        }
    }
}