/**
 * BossStatus.cpp
 *
 * ゾンビのステータス
 */
#include "stdafx.h"
#include "src/Actor/Enemy/Boss/BossStatus.h"
#include "src/core/ParameterManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			BossStatus::BossStatus()
			{
				ParameterManager::Get().LoadParameter<MasterBossStatus>("Assets/Status/Enemy/BossStatus.json", [](const nlohmann::json& j, MasterBossStatus& p)
					{
						p.m_moveSpeed = j["MoveSpeed"].get<float>();
						p.m_hp = j["HP"].get<uint16_t>();
						p.m_attackPower = j["AttackPower"].get<uint16_t>();
						p.m_attackFrequency = j["AttackFrequency"].get<float>();
						p.m_attackRange = j["AttackRange"].get<float>();
					});

				auto* parameter = ParameterManager::Get().GetParameter<MasterBossStatus>();
				m_moveSpeed = parameter->m_moveSpeed;
				m_hp = parameter->m_hp;
				m_maxHp = parameter->m_hp;
				m_attackPower = parameter->m_attackPower;
				m_attackFrequency = parameter->m_attackFrequency;
				m_attackRange = parameter->m_attackRange;
			}


			BossStatus::~BossStatus()
			{
				ParameterManager::Get().UnloadParameter<MasterEnemyStatus>();
			}			
		}
	}
}