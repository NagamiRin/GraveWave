/**
 * GunBase.h
 *
 * 銃の基底クラス
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	class RecoilSystem;


	namespace nsActor
	{
		namespace nsGun
		{
			/**
			 * 銃の基底クラス
			 */
			class GunBase : public Actor
			{
				/** 残段数の可変領域 */
				using MagazineValue = uint16_t;


			protected:
				/** 反動処理クラスのインスタンス */
				RecoilSystem* m_recoilSystem = nullptr;
				/** リロード中か */
				bool m_isReloading = false;
				/** 銃を装備中か */
				bool m_isEquipment = false;
				/** この種類の銃を所持しているか */
				bool m_isPossession = false;
				/** ADS中か */
				bool m_isADS = false;
				/** ダメージ量 */
				uint8_t m_damage = 0;
				/** 最大弾数 */
				MagazineValue m_maxAmmo = 0;
				/** 残弾数 */
				MagazineValue m_remainingAmmo = 0;
				/** 高さの初期値 */
				float m_initialHeight = 0.0f;
				/** 発射初速 */
				float m_bulletSpeed = 0.0f;
				/** 発射クールタイム */
				float m_fireCoolTime = 0.0f;
				/** 残りの発射クールタイム(秒) */
				float m_currentFireCoolTime = 0.0f;
				/** ADSの経過時間 */
				float m_currentADSTime = 0.0f;
				/** リロード時間 */
				float m_reloadTime = 0.0f;
				/** 武器切り替え時間 */
				float m_switchTime = 0.0f;
				/** 現在の銃のアニメーション時間 */
				float m_currentGunAnimTime = 0.0f;
				/** 現在のリロード時間 */
				float m_currentReloadTime = 0.0f;
				/** 銃の拡大倍率 */
				float m_zoomAngle = Math::DegToRad(60.0f);
				/** ADS移行時間 */
				float m_ADSTime = 0.0f;
				/** 弾丸の射出方向 */
				Vector3 m_injectionDirection = Vector3::Zero;
				/** 腰だめ撃ちの銃の位置 */
				Vector3 m_hipFirePosition = Vector3::Zero;
				/** ADSの銃の位置 */
				Vector3 m_ADSFirePosition = Vector3::Zero;
				/** 計算後の銃の位置 */
				Vector3 m_adjustPosition = Vector3::Zero;
				/** 反動の位置 */
				Vector3 m_recoilPosition = Vector3::Zero;
				/** プレイヤーの位置 */
				Vector3 m_playerPosition = Vector3::Zero;
				// 銃の調整位置
				Vector3 m_offsetPosition = Vector3::Zero;
				//
				Vector3 m_prevPosition = Vector3::Zero;
				/** 銃の名前 */
				std::string m_gunName;


			public:
				using SuperClass = GunBase;


			public:
				GunBase();
				virtual ~GunBase();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;


			public:
				/** ADSの処理 */
				void OnADS();
				/** 弾発射 */
				void OnFire();
				/** リロード */
				void Reload();
				/** リロード完了 */
				virtual void ReloadCompletion();
				/** リロードアニメーション */
				void ReloadAnimation();
				/** 武器をしまう */
				void PutGun();
				/** 銃を出す */
				void TakeOutGun();
				/** 銃口の位置を更新 */
				Vector3 SearchMuzzlePos();


			public:
				//銃の向きを設定
				void SetDirection(const Vector3& direction) override
				{
					m_direction = direction;
				}


			public:
				/** 情報をいろいろ更新 */
				void InformationUpdate(const Vector3& position, const Vector3& direction) {
					m_playerPosition = position;
					m_injectionDirection = direction;
					SetDirection(direction);
				}


			public:
				/** トランスフォームの親を設定 */
				inline void SetParent(Transform* t) { m_transform.SetParent(t); }
				/** 銃装備の状態を取得 */
				inline bool IsEquipment() const { return m_isEquipment; }
				/** 銃装備の状態を設定 */
				inline void SetIsEquipment(const bool equipment) { m_isEquipment = equipment; }
				/** 発射クールタイムを取得 */
				inline float GetFireCoolTime() { return m_currentFireCoolTime; }
				/** 現在の弾数を取得 */
				inline uint8_t GetRemainingAmmo() { return m_remainingAmmo; }
				/** 最大弾数を取得 */
				inline uint8_t GetMaxAmmo() { return m_maxAmmo; }
				/** 銃の名前を取得 */
				inline const std::string& GetGunName() const { return m_gunName; }
				/** リロード時間を取得 */
				inline float GetReloadTime() { return m_reloadTime; }
				/** 現在のリロード時間を取得 */
				inline float GetCurrentReloadTime() { return m_currentReloadTime; }
				/** ADSかを設定 */
				inline void SetADS(const bool ads)
				{
					m_isADS = ads;
					m_currentADSTime = 0.0f;
					m_prevPosition = m_offsetPosition;
				}
				/** 反動位置を取得 */
				Vector2 GetRecoil();
				/** 武器所持のフラグを設定 */
				inline void SetPossession(const bool possession) {
					m_isPossession = possession;						
				}
				/** 武器所持のフラグを取得 */
				inline bool IsPossession() const { return m_isPossession; }
			};
		}
	}
}