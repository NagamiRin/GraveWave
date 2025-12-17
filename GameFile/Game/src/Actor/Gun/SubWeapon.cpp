/**
 * SubWeapon.cpp
 *
 * サブ武器クラス
 */
#include "stdafx.h"
#include "SubWeapon.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/core/ParameterManager.h"



namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			SubWeapon::SubWeapon()
			{
				constexpr const char* MODEL_PATH = "Assets/ModelData/Gun/SubWeapon/GZ75.tkm";
				m_model.Init(MODEL_PATH);

				ParameterManager::Get().LoadParameter<MasterSubWeaponParameter>("Assets/Parameter/Gun/SubWeapon/CZ75Parameter.json", [](const nlohmann::json& j, MasterSubWeaponParameter& p)
					{
						p.m_gunName = j["GunName"].get<std::string>();
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

				auto* parameter = ParameterManager::Get().GetParameter<MasterSubWeaponParameter>();
				m_gunName = parameter->m_gunName;
				m_damage = parameter->m_damage;
				m_maxAmmo = parameter->m_maxAmmo;
				m_reloadTime = parameter->m_reloadTime;
				m_switchTime = parameter->m_switchTime;
				m_bulletSpeed = parameter->m_bulletSpeed;
				m_fireCoolTime = parameter->m_fireCoolTime;

				m_offsetPosition = Vector3(parameter->m_newPositionX, parameter->m_newPositionY, parameter->m_newPositionZ);
				m_transform.m_localScale = Vector3::One * 2.0f;

				m_remainingAmmo = m_maxAmmo;
			}


			SubWeapon::~SubWeapon()
			{
				ParameterManager::Get().UnloadParameter<MasterGunParameter>();
			}


			bool SubWeapon::Start()
			{
				return true;
			}


			void SubWeapon::Update()
			{
				SuperClass::Update();
			}		


			void SubWeapon::Render(RenderContext& rc)
			{
				SuperClass::Render(rc);
			}
		}
	}
}