/**
 * GunBase.cpp
 *
 * 銃の基底クラス
 */
#include "stdafx.h"
#include "src/Actor/Bullet/BulletManager.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/Actor/Gun/GunBase.h"
#include "src/Core/BattleManager.h"
#include "src/Effect/EffectManager.h"
#include "src/RecoilSystem.h"
#include "src/Sound/SoundManager.h"


namespace {
	const Vector3 ADS_POS = Vector3(0.0f, 10.0f, 10.0f);
	constexpr float RELOAD_GUN_YPOSITION = -20.0f;
	constexpr float GUN_PUT_YPOSITION = -30.0f;
}


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			GunBase::GunBase()
			{
				//反動処理クラスを生成
				m_recoilSystem = new RecoilSystem();
			}


			GunBase::~GunBase()
			{
				//反動処理クラスを削除
				delete m_recoilSystem;
			}


			bool GunBase::Start()
			{
				return true;
			}


			void GunBase::Update()
			{
				//発砲のクールタイムを数える
				m_currentFireCoolTime -= g_gameTime->GetFrameDeltaTime();
				if (m_currentFireCoolTime <= 0.0f) m_currentFireCoolTime = 0.0f;

				//リロードの経過時間を数える
				m_currentReloadTime -= g_gameTime->GetFrameDeltaTime();
				if (m_currentReloadTime <= 0.0f) m_currentReloadTime = 0.0f;

				//リロードアニメーション
				if (m_currentReloadTime >= 0.0f && m_isReloading) ReloadAnimation();

				//ADSの銃の位置を計算
				OnADS();

				//反動処理の更新
				m_recoilSystem->Update();

				//位置更新
				m_transform.m_localPosition = m_offsetPosition + m_adjustPosition;

				//銃の向きを更新
				Quaternion t = Quaternion::Identity;
				m_transform.m_localRotation = t;					

				//transformの更新
				m_transform.UpdateTransform();

				//モデルの更新
				m_model.SetPosition(m_transform.m_position);
				m_model.SetRotation(m_transform.m_rotation);
				m_model.SetScale(m_transform.m_localScale);
				m_model.Update();
			}


			void GunBase::OnADS()
			{
				float t = 1.0f;

				//ADS移行の補完率を求める
				if (m_currentADSTime < m_ADSTime) {
					m_currentADSTime += g_gameTime->GetFrameDeltaTime();

					t = m_currentADSTime / m_ADSTime;

					if (t >= 1.0f) {
						t = 0.0f;
					}
				}				

				//ADSの目標位置
				Vector3 targetPos = m_isADS ? m_ADSFirePosition : m_hipFirePosition;

				//銃の調整位置を、現在のADSの移行具合で変える
				m_offsetPosition = Math::Lerp<Vector3>(t, m_prevPosition, targetPos);
			}


			void GunBase::OnFire()
			{
				//発砲クールタイムが終わった、弾がまだある、リロード中でないなら
				if (m_currentFireCoolTime > 0.0f || m_remainingAmmo <= 0 || m_isReloading)return;

				//弾を生成
				nsBullet::NormalBullet* bullet = nullptr;
				Vector3 injectionDirection = g_camera3D->GetTarget() - m_transform.m_position;
				injectionDirection.Normalize();
				nsBullet::BulletManager::GetInstance()->CreatBullet<nsBullet::NormalBullet>(m_transform.m_position, injectionDirection, m_bulletSpeed, m_damage);

				//反動を加算
				m_recoilSystem->AddRecoil();

				//効果音、エフェクト
				SoundManager::Get().PlaySE(enSoundKind_HandGun_Fire);
				Vector3 effectPosition = SearchMuzzlePos();
				EffectManager::Get().PlayEffect(enEffectKind_Fire, effectPosition, GetRotation(), Vector3::One * 0.1f);

				//クールタイムをセット
				m_currentFireCoolTime = m_fireCoolTime;

				//残弾数を減らす
				if (m_remainingAmmo > 0)m_remainingAmmo--;
			}


			void GunBase::Reload()
			{
				//リロード中でない、予備弾がまだある、残弾がmaxでないなら
				if (m_isReloading || 
					m_currentReloadTime < 0.0f ||
					(nsCore::BattleManager::GetInstance()->GetSpareAmmo() <= 0) ||
					m_remainingAmmo == m_maxAmmo)return;

				//リロード中にする
				m_isReloading = true;
				m_currentReloadTime = m_reloadTime;		

				//SE
				SoundManager::Get().PlaySE(enSoundKind_HandGun_Reload);
			}


			void GunBase::ReloadCompletion()
			{
				//インベントリの弾数を減らす
				//予備弾数が不足しているなら,ある分だけ装填
				const MagazineValue shotAmount = m_maxAmmo - m_remainingAmmo;
				const uint16_t spareAmmo = nsCore::BattleManager::GetInstance()->GetSpareAmmo();
				if (shotAmount >= spareAmmo) {
					m_remainingAmmo += spareAmmo;
				}
				else {
					m_remainingAmmo = m_maxAmmo;
				}

				nsCore::BattleManager::GetInstance()->LoadAmmo(shotAmount);

				m_isReloading = false;
			}


			void GunBase::ReloadAnimation()
			{
				float t = 0.0f;

				//リロード時間の補完率を求める
				//リロード時間が半分を過ぎているなら補完率を反転
				if (m_currentReloadTime >= m_reloadTime / 2) {
					t = m_currentReloadTime / m_reloadTime;
					t = 1.0f - t;
				}
				else if (m_currentReloadTime <= m_reloadTime / 2) {
					t = m_currentReloadTime / (m_reloadTime / 2);
				}

				//銃のY位置を設定
				m_adjustPosition.y = RELOAD_GUN_YPOSITION * t;
				
				//リロードが終わったなら完了処理へ
				if (m_currentReloadTime <= 0.0f)ReloadCompletion();
			}


			void GunBase::PutGun()
			{
				//銃をしまう処理
				m_currentGunAnimTime += g_gameTime->GetFrameDeltaTime();
				const float targetPos = GUN_PUT_YPOSITION;
				float t = m_currentGunAnimTime / m_switchTime;
				if (t >= 1.0f) t = 1.0f;
				const float currentPos = targetPos * t;

				m_adjustPosition = Vector3(0.0f, currentPos, 0.0f);

				if (t >= 1.0f) {
					m_currentGunAnimTime = 0.0f;
					m_isEquipment = false;
				}
			}


			void GunBase::TakeOutGun()
			{
				//銃を取り出す処理
				m_currentGunAnimTime += g_gameTime->GetFrameDeltaTime();
				const float startPos = GUN_PUT_YPOSITION;
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
				//銃モデルの銃口の位置を探す
				//銃口の位置にメッシュパーツを設置している
				//銃口のメッシュパーツはリストの最後にある
				//銃口の位置を取得して返す
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
				//装備なら描画
				if (m_isEquipment) {
					m_model.Draw(rc);
				}
			}


			Vector2 GunBase::GetRecoil()
			{
				return m_recoilSystem->GetRecoil();
			}
		}
	}
}