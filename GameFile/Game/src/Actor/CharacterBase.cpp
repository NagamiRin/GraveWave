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
			SuperClass::Update();

			m_transform.UpdateTransform();
		}

		
		void CharacterBase::Render(RenderContext& rc)
		{
		}
	}
}
