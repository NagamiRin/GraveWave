/**
 * EnemyBase.cpp
 *
 * エネミーの基底クラス
 */
#include "stdafx.h"
#include "src/Actor/Enemy/EnemyBase.h"
#include "src/Core/BattleManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			EnemyBase::EnemyBase()
			{
				m_gravityAmount = nsCore::BattleManager::GetInstance()->GetGravityAmount();
			}


			EnemyBase::~EnemyBase()
			{
			}


			bool EnemyBase::Start()
			{
				return true;
			}


			void EnemyBase::Update()
			{
				//進行できる範囲に制限を設ける
				if (m_transform.m_localPosition.z <= m_stopPosition) m_transform.m_localPosition.z = m_stopPosition;

				ApplyGravity();

				SuperClass::Update();
			}


			void EnemyBase::Render(RenderContext& rc)
			{
			}
		}
	}
}