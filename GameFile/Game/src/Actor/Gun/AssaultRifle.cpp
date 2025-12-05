/**
 * AssaultRifle.cpp
 *
 * アサルトライフルクラス
 */
#include "stdafx.h"
#include "AssaultRifle.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/core/ParameterManager.h"



namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			AssaultRifle::AssaultRifle()
			{
				constexpr const char* MODEL_PATH = "Assets/ModelData/Gun/MainWeapon/AK-47.tkm";
				m_model.Init(MODEL_PATH);

				ParameterManager::Get().LoadParameter<MasterGunParameter>("Assets/Parameter/Gun/MainWeapon/M4A1Parameter.json", [](const nlohmann::json& j, MasterGunParameter& p)
					{
						p.m_damage = j["Damage"].get<uint8_t>();
						p.m_maxAmmo = j["MaxAmmo"].get<uint8_t>();
						p.m_reloadTime = j["ReloadTime"].get<float>();
						p.m_switchTime = j["SwitchTime"].get<float>();
						p.m_bulletSpeed = j["BulletSpeed"].get<float>();
						p.m_fireCoolTime = j["FireCoolTime"].get<float>();
						p.m_newPositionX = j["NewPositionX"].get<float>();
						p.m_newPositionY = j["NewPositionY"].get<float>();
						p.m_newPositionZ = j["NewPositionZ"].get<float>();
					});

				auto* parameter = ParameterManager::Get().GetParameter<MasterGunParameter>();
				m_damage = parameter->m_damage;
				m_maxAmmo = parameter->m_maxAmmo;
				m_reloadTime = parameter->m_reloadTime;
				m_switchTime = parameter->m_switchTime;
				m_bulletSpeed = parameter->m_bulletSpeed;
				m_fireCoolTime = parameter->m_fireCoolTime;

				m_offsetPosition = Vector3(parameter->m_newPositionX, parameter->m_newPositionY, parameter->m_newPositionZ);

				m_remainingAmmo = m_maxAmmo;
			}


			AssaultRifle::~AssaultRifle()
			{
				ParameterManager::Get().UnloadParameter<MasterGunParameter>();
			}


			bool AssaultRifle::Start()
			{
				return true;
			}


			void AssaultRifle::Update()
			{
				SuperClass::Update();
			}


			void AssaultRifle::Render(RenderContext& rc)
			{
				m_model.Draw(rc);
			}
		}
	}
}