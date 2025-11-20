/**
 * EnemyBase.h
 * 
 * エネミーの基底クラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/** エネミーの行動状態の種類。 */
			enum EnEnemyActionVar {
				enStandby,		//スタンバイ。フィールド上に出現していない状態。
				enProgress,		//進行。
				enAttack,		//攻撃。
				enHit,			//被弾。
				enDead,			//死亡。
			};


			class EnemyBase :public CharacterBase
			{
				using SuperClass = CharacterBase;


			protected:
				/** 現在の行動状態。 */
				int m_currentState = 0;
				/** 重力量 */
				float m_gravityAmount = 0.0f;
				/** 進行を止める距離（Ｚ座標） */
				float m_stopPosition = 0.0f;
				/** プレイヤーの位置情報 */
				Vector3 m_playerPosition = Vector3::Zero;
				/** 進行方向 */
				Vector3 m_moveDirection = Vector3::Zero;
				/** コリジョンオブジェクト */
				CollisionObject* m_collisionObject = nullptr;


			public:
				/** コンストラクタ */
				EnemyBase();
				/** デストラクタ */
				virtual ~EnemyBase();


			public:
				/** 生成時に一度だけ呼ばれる関数。 */
				virtual bool Start()override;
				/** 毎フレーム呼ばれる更新処理。 */
				virtual void Update()override;
				/** 描画処理。 */
				virtual void Render(RenderContext& rc)override;


			public:
				/** プレイヤーの位置情報を更新 */
				inline void UpdatePlayerPosition(const Vector3& position) { m_playerPosition = position; }
				/** プレイヤーの位置情報を取得 */
				inline const Vector3& GetPlayerPosition() const { return m_playerPosition; }
				/** 進行を止める位置を設定 */
				inline void SetStopPosition(const float position) { m_stopPosition = position; }
				/** 進行を止める位置を取得 */
				inline float GetStopPosition()const { return m_stopPosition; }
				/** 移動方向を設定 */
				inline void SetMoveDirection(const Vector3& direction) { m_moveDirection = direction; }
				/** 移動方向を取得 */
				inline const Vector3& GetMoveDirection()const { return m_moveDirection; }
				/** 重力を適応させる */
				inline void ApplyGravity() {
					m_transform.m_localPosition.y = m_gravityAmount;
					if (m_transform.m_localPosition.y <= 0.0f)m_transform.m_localPosition.y = 0.0f;
				}
			};
		}
	}
}