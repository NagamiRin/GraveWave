/**
 * BossStateMachine.h
 *
 * ボスの状態遷移を行うステートマシン
 */
#pragma once
#include "src/Actor/StateMachine.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class Boss;
			class BossStatus;


			/**
			 * ボスステートマシンクラス
			 */

			class BossStateMachine : public StateMachine
			{
			private:
				/** StateMachineを親クラスとする */
				using SuperClass = StateMachine;

				/** オーナー(ゾンビ) */
				Boss* m_owner = nullptr;
				/** オーナーのステータス */
				BossStatus* m_ownerStatus = nullptr;
				/** ヒットアニメーション中か */
				bool m_isHitting = false;
				/** ヒットリアクションを行った回数 */
				uint8_t m_reactionNum = 0;


			public:
				/** コンストラクタ */
				BossStateMachine();
				/** デストラクタ */
				~BossStateMachine();

				/** 更新処理 */
				virtual void Update() override;


			public:
				/** 状態切り替え */
				void ChangeState();
				/** 死亡状態に切り替えができるか */
				bool CanChangeToDeathState()const;
				/** 被弾状態に切り替えができるか */
				bool CanChangeToHitState()const;
				/** 岩投げ状態に切り替えができるか */
				bool CanChangeToThrowState()const;				
				/** 歩き状態に切り替えができるか */
				bool CanChangeToWalkState() const;
				/** 初期設定を行う */
				void Setup(Boss* zombie, BossStatus* zombieStatus);


			public:
				/**
				 * ゾンビ取得
				 * NOTE: 各Stateでのみ使用予定
				 */
				Boss* GetOwner() { return m_owner; }
				/** 移動方向を設定 */
				void SetMoveDirection(const Vector3& direction);
				/** 移動方向を取得 */
				const Vector3& GetMoveDirection()const;
				/** 移動速度を取得 */
				float GetMoveSpeed()const;
				/** 攻撃力を取得 */
				uint16_t GetAttackPower()const;
				/** 攻撃範囲を取得 */
				float GetAttackRange() const;
				/** 攻撃速度を取得 */
				float GetDealingDamage()const;
				/** 位置を設定 */
				void SetPosition(const Vector3& position);
				/** 位置を取得 */
				const Vector3& GetPosition()const;
				/** 向きを設定 */
				void SetDirection(const Vector3& direction);
				/** プレイヤーの位置情報を取得 */
				const Vector3& GetPlayerPosition() const;

				/** ヒットアニメーション中のフラグを設定 */
				inline void SetHitting(const bool hit) { m_isHitting = hit; }
				/** ヒットリアクションの回数を加算 */
				inline void AddReactionNum() { m_reactionNum++; }
			};
		}
	}
}


