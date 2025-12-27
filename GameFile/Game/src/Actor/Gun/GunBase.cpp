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

				OnADS();
				m_recoilSystem->Update();

				m_transform.m_localPosition = m_offsetPosition + m_adjustPosition;

				// @todo for test
				// 銃を反動に応じて上に向かせたい
				{
					Quaternion t = Quaternion::Identity;
					//Vector3 recoilDirection = Vector3(m_recoilSystem->GetRecoil().x, m_recoilSystem->GetRecoil().y, 0.0f);
					//if (recoilDirection.Length() > 0.001f) {
					//	recoilDirection *= 0.1f;
					//	recoilDirection += m_direction;
					//	// 1. 前方ベクトル(Z)の正規化
					//	Vector3 zAxis = recoilDirection;
					//	zAxis.Normalize();

					//	// 2. 右ベクトル(X)の算出 (Y軸(0,1,0) と Z軸の外積)
					//	// 注意: 方向が真上や真下に近いと外積がゼロになり計算不能になるため、
					//	// 実戦ではここで「ZとUpが平行でないか」のチェックを入れるのが安全です。
					//	Vector3 xAxis = Vector3::Up;
					//	xAxis.Cross(recoilDirection);
					//	xAxis.Normalize();
					//	// 3. 真の上ベクトル(Y)の算出 (Z軸 と X軸の外積)
					//	// 既に直交しているので正規化は理論上不要だが、誤差対策ですることもある
					//	Vector3 yAxis = zAxis;
					//	yAxis.Cross(xAxis);

					//	// 4. 回転行列の構築
					//	// DirectXは行優先(Row-Major)か列優先(Column-Major)かによりますが、
					//	// XMMATRIXは通常、基底ベクトルを行にセットします。
					//	Matrix rotMatrix = Matrix::Identity;
					//	memcpy(&rotMatrix.m[0], &xAxis, sizeof(xAxis)); // X軸
					//	memcpy(&rotMatrix.m[1], &yAxis, sizeof(yAxis)); // Y軸
					//	memcpy(&rotMatrix.m[2], &zAxis, sizeof(zAxis)); // Z軸

					//	t.SetRotation(rotMatrix);
					//}
					m_transform.m_localRotation = t;
				}

				m_transform.UpdateTransform();

				m_model.SetPosition(m_transform.m_position);
				m_model.SetRotation(m_transform.m_rotation);
				m_model.SetScale(m_transform.m_localScale);
				m_model.Update();
			}


			void GunBase::OnADS()
			{
				m_currentADSTime += g_gameTime->GetFrameDeltaTime();

				float t = m_currentADSTime / m_ADSSpeed;

				if (t >= 1.0f) {
					t = 0.0f;
				}

				// 目的位置
				Vector3 targetPos = m_isADS ? m_ADSFirePosition : m_hipFirePosition;

				m_offsetPosition = Math::Lerp<Vector3>(t, m_prevPosition, targetPos);
			}


			void GunBase::OnFire()
			{
				if (m_currentCoolTime > 0.0f || m_remainingAmmo <= 0 || m_isReloading)return;

				nsBullet::NormalBullet* bullet = nullptr;
				// 弾を生成

				// @todo for test
				Vector3 injectionDirection = g_camera3D->GetTarget() - m_transform.m_position;
				injectionDirection.Normalize();
				nsBullet::BulletManager::GetInstance()->CreatBullet<nsBullet::NormalBullet>(m_transform.m_position, injectionDirection, m_bulletSpeed, m_damage);

				//反動を加算
				m_recoilSystem->AddRecoil();

				//効果音、エフェクト
				SoundManager::Get().PlaySE(enSoundKind_HandGun_Fire);

				Vector3 effectPosition = /*GetPosition() + */SearchMuzzlePos();
				EffectManager::Get().PlayEffect(enEffectKind_Fire, effectPosition, GetRotation(), Vector3::One * 0.1f);

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

				//SE
				SoundManager::Get().PlaySE(enSoundKind_HandGun_Reload);
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

				m_adjustPosition.y = -20.0f * t;
				//m_transform.m_localPosition += Vector3(0.0f, adjustPosition, 0.0f);
				
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


			Vector3 GunBase::SearchMuzzlePos()
			{
				const auto& meshPartsList = m_model.GetModel().GetTkmFile().GetMeshParts();
				auto& meshParts = meshPartsList[meshPartsList.size() - 1];

				Transform tempTransform;
				tempTransform.SetParent(&m_transform);

				Vector3 pos = meshParts.vertexBuffer[0].pos;
				{
					float temp = pos.y;
					pos.y = pos.z;
					pos.z = temp * -1.0f;
				}
				if (m_isADS) {
					pos.y += 0.05f;
				}

				tempTransform.m_localPosition = pos;
				tempTransform.UpdateTransform();

				return tempTransform.m_position;
			}


			void GunBase::Render(RenderContext& rc) 
			{
				m_model.Draw(rc);				
			}
		}
	}
}