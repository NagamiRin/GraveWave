/**
 * PlayerStatus.cpp
 *
 * プレイヤーのステータス
 */
#include "stdafx.h"
#include "src/Actor/Player/PlayerStatus.h"
#include "src/core/ParameterManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			PlayerStatus::PlayerStatus()
			{
				ParameterManager::Get().LoadParameter<MasterPlayerStatus>("Assets/Status/player/PlayerStatus.json", [](const nlohmann::json& j, MasterPlayerStatus& p)
					{
						p.m_moveSpeed = j["MoveSpeed"].get<float>();
					});
			}


			PlayerStatus::~PlayerStatus()
			{
				ParameterManager::Get().UnloadParameter<MasterPlayerStatus>();
			}


			void PlayerStatus::Setup()
			{
				auto* parameter = ParameterManager::Get().GetParameter<MasterPlayerStatus>();
				m_moveSpeed = parameter->m_moveSpeed;
			}
		}
	}
}