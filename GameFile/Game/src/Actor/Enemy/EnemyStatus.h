/**
 * EnemyStatus.h
 *
 * エネミーステータス
 */
#pragma once

#include "src/Actor/ActorStatus.h"

namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/**
			 * エネミーのステータスクラス
			 */
			class EnemyStatus : public ActorStatus
			{
			protected:
				/** 体力 */
				uint16_t m_hp = 0;
				/** 最大体力 */  
				uint16_t m_maxHp = 0;
				/** 攻撃力 */
				uint16_t m_attackPower = 0;
				/** 近接攻撃の攻撃頻度 */
				float m_attackFrequency = 0.0f;
				/** 攻撃範囲 */
				float m_attackRange = 0.0f;
				/** 移動速度 */
				float m_moveSpeed = 0.0f;
				/** 移動方向 */
				Vector3 m_moveDirection = Vector3::Zero;


			public:
				EnemyStatus();
				~EnemyStatus();


			public:
				/** セットアップ */
				void Setup() override;


			public:
				/** エネミーの最大HPを取得 */
				inline float GetMaxHP()const { return m_maxHp; }
				/** エネミーのHPを取得 */
				inline uint16_t GetHP() const { return m_hp; }
				/** エネミーのHPを設定 */
				inline void SetHP(const uint16_t hp) { m_hp = hp; }
				/** エネミーのHPをリセット */
				inline void ResetHP() { m_hp = m_maxHp; }
				/** エネミーの攻撃力を取得 */
				inline uint16_t GetAttackPower()const { return m_attackPower; }
				/** 近接攻撃の攻撃速度を取得 */
				inline float GetAttackFrequency()const { return m_attackFrequency; }
				/** 攻撃範囲を取得 */
				inline float GetAttackRange() const { return m_attackRange; }
				/** エネミーの移動速度を取得 */
				inline float GetMoveSpeed() const { return m_moveSpeed; }
				/** 移動速度を適応 */
				inline void ApplySpeed(Vector3& position) {
					m_moveDirection.Normalize();
					position = m_moveDirection * m_moveSpeed;
				}			
			};
		}
	}
}