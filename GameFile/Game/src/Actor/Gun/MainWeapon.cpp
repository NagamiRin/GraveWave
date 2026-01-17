/**
 * MainWeapon.cpp
 *
 * メイン武器クラス
 */
#include "stdafx.h"
#include "MainWeapon.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/core/ParameterManager.h"


namespace {
	const Vector3 ADS_POSITION = Vector3{ 0.0f, -0.15f, 0.35 };
	constexpr float ADS_TIME = 0.1f;
}

namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			MainWeapon::MainWeapon()
			{
				constexpr const char* MODEL_PATH = "Assets/ModelData/Gun/MainWeapon/AK-47.tkm";
				m_model.Init(MODEL_PATH);

				//外部からパラメーターを読み込む
				ParameterManager::Get().LoadParameter<MasterGunParameter>("Assets/Parameter/Gun/MainWeapon/M4A1Parameter.json", [](const nlohmann::json& j, MasterGunParameter& p)
					{
						p.m_gunName = j["GunName"].get<std::string>();
						p.m_damage = j["Damage"].get<uint8_t>();
						p.m_maxAmmo = j["MaxAmmo"].get<uint8_t>();
						p.m_reloadTime = j["ReloadTime"].get<float>();
						p.m_switchTime = j["SwitchTime"].get<float>();
						p.m_bulletSpeed = j["BulletSpeed"].get<float>();
						p.m_currentFireCoolTime = j["FireCoolTime"].get<float>();
						p.m_newPositionX = j["NewPositionX"].get<float>();
						p.m_newPositionY = j["NewPositionY"].get<float>();
						p.m_newPositionZ = j["NewPositionZ"].get<float>();
					});

				//各パラメーターをセット
				auto* parameter = ParameterManager::Get().GetParameter<MasterGunParameter>();
				m_gunName = parameter->m_gunName;
				m_damage = parameter->m_damage;
				m_maxAmmo = parameter->m_maxAmmo;
				m_reloadTime = parameter->m_reloadTime;
				m_switchTime = parameter->m_switchTime;
				m_bulletSpeed = parameter->m_bulletSpeed;
				m_currentFireCoolTime = parameter->m_currentFireCoolTime;

				//腰だめ撃ちの位置を設定
				m_hipFirePosition = Vector3(parameter->m_newPositionX, parameter->m_newPositionY, parameter->m_newPositionZ);

				//ADSの位置を設定
				m_ADSFirePosition = Vector3(ADS_POSITION);

				//ADS移行速度を設定
				m_ADSTime = ADS_TIME;

				//弾を装填
				m_remainingAmmo = m_maxAmmo;
			}


			MainWeapon::~MainWeapon()
			{
				//パラメーターを削除
				ParameterManager::Get().UnloadParameter<MasterGunParameter>();
			}


			bool MainWeapon::Start()
			{
				return true;
			}


			void MainWeapon::Update()
			{
				//debugの時だけ、ホットリロードの数値変更を受け付ける
#ifdef APP_PARAM_HOT_RELOAD
				auto* parameter = ParameterManager::Get().GetParameter<MasterGunParameter>();
				
				m_gunName = parameter->m_gunName;
				m_damage = parameter->m_damage;
				m_maxAmmo = parameter->m_maxAmmo;
				m_reloadTime = parameter->m_reloadTime;
				m_switchTime = parameter->m_switchTime;
				m_bulletSpeed = parameter->m_bulletSpeed;
				m_fireCoolTime = parameter->m_currentFireCoolTime;
#endif

				//親クラスの更新
				SuperClass::Update();
			}


			void MainWeapon::Render(RenderContext& rc)
			{
				//親クラスの描画処理
				SuperClass::Render(rc);
			}
		}
	}
}