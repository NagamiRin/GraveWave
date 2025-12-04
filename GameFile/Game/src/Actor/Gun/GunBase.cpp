/**
 * GunBase.cpp
 *
 * 銃の基底クラス
 */
#include "stdafx.h"
#include "src/Actor/Gun/GunBase.h"
#include "src/Actor/Bullet/BulletManager.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/Effect/EffectManager.h"
#include "src/Sound/SoundManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			GunBase::GunBase()
			{
			}


			GunBase::~GunBase()
			{
			}


			bool GunBase::Start()
			{
				return true;
			}


			void GunBase::Update()
			{
				m_currentCoolTime -= g_gameTime->GetFrameDeltaTime();
				if (m_currentCoolTime <= 0.0f) m_currentCoolTime = 0.0f;

				m_currentReloadTime -= g_gameTime->GetFrameDeltaTime();
				if (m_currentReloadTime <= 0.0f) m_currentReloadTime = 0.0f;

				if (m_currentReloadTime >= 0.0f && m_isReloading)ReloadAnimation();

				m_transform.m_localPosition = m_playerPosition + m_offsetPosition + m_adjustPosition;

				m_model.SetPosition(m_transform.m_localPosition);
				m_model.SetRotation(m_transform.m_localRotation);
				m_model.Update();
			}


			void GunBase::OnFire()
			{
				if (m_currentCoolTime > 0.0f || m_remainingAmmo <= 0 || m_isReloading)return;

				nsBullet::NormalBullet* bullet = nullptr;
				// 弾を生成
				nsBullet::BulletManager::GetInstance()->CreatBullet<nsBullet::NormalBullet>(m_transform.m_localPosition, m_injectionDirection, m_bulletSpeed, m_damage);			

				//効果音、エフェクト
				SoundManager::Get().PlaySE(enSoundKind_HandGun_Fire);
				EffectManager::Get().PlayEffect(enEffectKind_Fire, GetPosition() + (GetDirection() * 30.0f), GetRotation(), Vector3::One);

				//クールタイムをセット
				m_currentCoolTime = m_fireCoolTime;

				//残弾数を減らす
				if (m_remainingAmmo > 0)m_remainingAmmo--;
			}


			void GunBase::Reload()
			{
				if (m_isReloading || m_currentReloadTime < 0.0f || m_remainingAmmo == m_maxAmmo)return;

				m_isReloading = true;
				m_currentReloadTime = m_reloadTime;				
			}


			void GunBase::ReloadCompletion()
			{
				m_remainingAmmo = m_maxAmmo;
				m_isReloading = false;
			}


			void GunBase::ReloadAnimation()
			{
				float t = 0.0f;

				if (m_currentReloadTime >= m_reloadTime / 2) {
					t = m_currentReloadTime / m_reloadTime;
					t = 1.0f - t;
				}
				else if (m_currentReloadTime <= m_reloadTime / 2) {
					t = m_currentReloadTime / (m_reloadTime / 2);
				}

				const float adjustPosition = -20.0f * t;
				m_transform.m_localPosition += Vector3(0.0f, adjustPosition, 0.0f);
				
				if (m_currentReloadTime <= 0.0f)ReloadCompletion();
			}


			void GunBase::PutGun()
			{
				m_currentGunAnimTime += g_gameTime->GetFrameDeltaTime();
				const float targetPos = -30.0f;
				float t = m_currentGunAnimTime / m_switchTime;
				if (t >= 1.0f) t = 1.0f;
				const float currentPos = targetPos * t;

				m_adjustPosition = Vector3(0.0f, currentPos, 0.0f);

				if (t == 1.0f) {
					m_currentGunAnimTime = 0.0f;
					m_isEquipment = false;
				}
			}


			void GunBase::TakeOutGun()
			{
				m_currentGunAnimTime += g_gameTime->GetFrameDeltaTime();
				const float startPos = -30.0f;
				float t = m_currentGunAnimTime / m_switchTime;
				if (t >= 1.0f) t = 1.0f;
				const float currentPos = startPos * (1 - t);

				m_adjustPosition = Vector3(0.0f, currentPos, 0.0f);

				if (t == 1.0f) {
					m_adjustPosition = Vector3::Zero;
					m_currentGunAnimTime = 0.0f;
					m_isEquipment = true;
				}
			}


			void GunBase::Render(RenderContext& rc) 
			{
				m_model.Draw(rc);				
			}
		}
	}
}