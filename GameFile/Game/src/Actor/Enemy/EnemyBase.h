/**
 * EnemyBase.h
 * 
 * エネミーの基底クラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"


namespace nsApp
{
	class ActorStatus;

	namespace nsActor
	{
		namespace nsEnemy
		{
			class EnemyBase :public CharacterBase
			{
				using SuperClass = CharacterBase;


			protected:
				/** ヘッドショットのコリジョン */
				CollisionObject* m_headCollision = nullptr;
				/** 被弾したか */
				bool m_isHit = false;
				/** 攻撃をしたか */
				bool m_isAttack = false;
				/** 攻撃状態か */
				bool m_isAttackState = false;
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
				/** 被弾中のフラグを取得 */
				inline const bool IsHit() { return m_isHit; }
				/** 被弾中のフラグを設定 */
				inline void SetHit(const bool hit) { m_isHit = hit; }			
				/** 攻撃のフラグを取得 */
				inline bool IsAttack() { return m_isAttack; }
				/** 攻撃のフラグを設定 */
				inline void SetAttack(const bool attack) { m_isAttack = attack; }
				/** 攻撃状態のフラグを取得 */
				inline bool IsAttackState() { return m_isAttackState; }
				/** 攻撃状態のフラグを設定 */
				inline void SetAttackState(const bool attack) { m_isAttackState = attack; }
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