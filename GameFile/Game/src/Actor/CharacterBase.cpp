/**
 * CharacterBase.cpp
 * 
 * キャラクターのベース
 */
#include "stdafx.h"
#include "src/Actor/CharacterBase.h"


namespace nsApp
{
	namespace nsActor
	{
		CharacterBase::CharacterBase()
		{
		}


		CharacterBase::~CharacterBase()
		{
		}

		
		bool CharacterBase::Start()
		{
			return true;
		}

		
		void CharacterBase::Update()
		{
			ApplySpeed();

			m_transform.UpdateTransform();
		}

		
		void CharacterBase::Render(RenderContext& rc)
		{
		}


		void CharacterBase::ApplySpeed()
		{
			Vector3 moveAmount = m_speed / g_gameTime->GetFrameDeltaTime();
			m_transform.m_localPosition += moveAmount;
		}
	}
}
