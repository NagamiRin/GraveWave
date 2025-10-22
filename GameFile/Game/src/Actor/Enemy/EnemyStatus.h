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
				/** 移動速度 */
				float m_moveSpeed = 0.0f;


			public:
				/** 移動速度を取得 */
				inline float GetMoveSpeed() const { return m_moveSpeed; }
				/** エネミーのHPを取得 */
				inline uint16_t GetHP() const { return m_hp; }
				/** エネミーのHPを設定 */
				inline void const SetHP(uint16_t hp) { m_hp = hp; }
				/** エネミーのHPをリセット */
				inline void const ResetHP() { m_hp = m_maxHp; }


			public:
				/** コンストラクタ */
				EnemyStatus();
				/** デストラクタ */
				~EnemyStatus();


				/** セットアップ */
				void Setup() override;
			};
		}
	}
}