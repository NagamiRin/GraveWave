/**
 * HandGun.cpp
 *
 * ハンドガンクラス
 */
#include "stdafx.h"
#include "src/Actor/Gun/HandGun.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/core/ParameterManager.h"



namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			HandGun::HandGun()
			{
				constexpr const char* MODEL_PATH = "Assets/ModelData/Gun/HundGun/HundGun.tkm";
				m_model.Init(MODEL_PATH);

				ParameterManager::Get().LoadParameter<MasterHandGunParameter>("Assets/Parameter/Gun/HandGunParameter.json", [](const nlohmann::json& j, MasterHandGunParameter& p)
					{
						p.m_damage = j["Damage"].get<uint8_t>();
						p.m_maxAmmo = j["MaxAmmo"].get<uint8_t>();
						p.m_reloadTime = j["ReloadTime"].get<float>();
						p.m_bulletSpeed = j["BulletSpeed"].get<float>();
						p.m_fireCoolTime = j["FireCoolTime"].get<float>();
						p.m_newPositionX = j["NewPositionX"].get<float>();
						p.m_newPositionY = j["NewPositionY"].get<float>();
						p.m_newPositionZ = j["NewPositionZ"].get<float>();
					});

				auto* parameter = ParameterManager::Get().GetParameter<MasterHandGunParameter>();
				m_damage = parameter->m_damage;
				m_maxAmmo = parameter->m_maxAmmo;
				m_reloadTime = parameter->m_reloadTime;
				m_bulletSpeed = parameter->m_bulletSpeed;
				m_fireCoolTime = parameter->m_fireCoolTime;

				m_offsetPosition = Vector3(parameter->m_newPositionX, parameter->m_newPositionY, parameter->m_newPositionZ);
				m_transform.m_localScale = Vector3::One * 0.5f;

				//// @todo for test
				//auto* tkmFile = g_engine->GetTkmFileFromBank(MODEL_PATH);
				//const auto& meshParts = tkmFile->GetMeshParts();
				//for (auto& mesh : meshParts) {
				//	Vector3 targetPos = mesh.vertexBuffer[0].pos;
				//	int test = 0;
				//}


				m_remainingAmmo = m_maxAmmo;
			}


			HandGun::~HandGun()
			{
				ParameterManager::Get().UnloadParameter<MasterHandGunParameter>();
			}


			bool HandGun::Start()
			{
				return true;
			}


			void HandGun::Update()
			{
				SuperClass::Update();
			}		


			void HandGun::Render(RenderContext& rc)
			{
				SuperClass::Render(rc);
			}
		}
	}
}