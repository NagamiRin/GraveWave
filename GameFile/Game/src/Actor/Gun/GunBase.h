/**
 * GunBase.h
 *
 * 銃の基底クラス
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			/**
			 * 銃の基底クラス
			 */
			class GunBase : public Actor
			{
			protected:
				/** リロード中か */
				bool m_isReloading = false;
				/** 銃を装備中か */
				bool m_isEquipment = false;
				/** ダメージ量 */
				uint8_t m_damage = 0;
				/** 最大弾数 */
				uint8_t m_maxAmmo = 0;
				/** 残弾数 */
				uint8_t m_remainingAmmo = 0;
				/** 高さの初期値 */
				float m_initialHeight = 0.0f;
				/** 発射初速 */
				float m_bulletSpeed = 0.0f;
				/** 発射クールタイム */
				float m_fireCoolTime = 0.0f;
				/** 残りの発射クールタイム(秒) */
				float m_currentCoolTime = 0.0f;
				/** リロード時間 */
				float m_reloadTime = 0.0f;
				/** 武器切り替え時間 */
				float m_switchTime = 0.0f;
				/** 現在の銃のアニメーション時間 */
				float m_currentGunAnimTime = 0.0f;
				/** 現在のリロード時間 */
				float m_currentReloadTime = 0.0f;
				/** 弾丸の射出方向 */
				Vector3 m_injectionDirection = Vector3::Zero;
				/** 計算後の銃の位置 */
				Vector3 m_adjustPosition = Vector3::Zero;
				/** プレイヤーの位置 */
				Vector3 m_playerPosition = Vector3::Zero;
				/** 銃の名前 */
				std::string m_gunName;

				// @todo for あとでコメント
				Vector3 m_offsetPosition = Vector3::Zero;


			public:
				using SuperClass = GunBase;


			public:
				/** コンストラクタ */
				GunBase();
				/** デストラクタ */
				virtual ~GunBase();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;


			public:
				/** 弾発射 */
				void OnFire();
				/** リロード */
				void Reload();
				/** リロード完了 */
				void ReloadCompletion();
				/** リロードアニメーション */
				void ReloadAnimation();
				/** 武器をしまう */
				void PutGun();
				/** 銃を出す */
				void TakeOutGun();


			public:
				void SetDirection(const Vector3& direction) override
				{
					m_direction = direction;
					Quaternion t;
					t = GetLocalRotation();

					// Y軸回転(横方向)
					t.SetRotationYFromDirectionXZ(m_direction);

					//// XZ軸回転(縦)
					//// 軸を求める
					//Vector3 xz;
					//xz.Cross(Vector3::Up, Vector3(direction.x, 0.0f, direction.z));

					//Vector3 temp = Vector3::Front;
					//const float shita = temp.Dot(Vector3(0.0f, direction.y, direction.z));
					//const float xzRotValue = acosf(shita);
					//K2_LOG("XRotValue: %f \n", Math::RadToDeg(xzRotValue));
					//Quaternion xzQ;
					//xzQ.SetRotation(xz, xzRotValue);

					//t.Multiply(xzQ);

					SetLocalRotation(t);
				}


			public:
				/** 情報を更新 */
				void InformationUpdate(const Vector3& position, const Vector3& direction) {
					m_playerPosition = position;
					m_injectionDirection = direction;
					SetDirection(direction);
				}


			public:
				/** 銃装備の状態を取得 */
				inline bool IsEquipment() const { return m_isEquipment; }
				/** 銃装備の状態を設定 */
				inline void SetIsEquipment(const bool equipment) { m_isEquipment = equipment; }
				/** 発射クールタイムを取得 */
				inline float GetFireCoolTime() { return m_currentCoolTime; }
				/** 現在の弾数を取得 */
				inline uint8_t GetRemainingAmmo() { return m_remainingAmmo; }
				/** 最大弾数を取得 */
				inline uint8_t GetMaxAmmo() { return m_maxAmmo; }
				/** 銃の名前を取得 */
				inline const std::string& GetGunName() const { return m_gunName; }
			};
		}
	}
}