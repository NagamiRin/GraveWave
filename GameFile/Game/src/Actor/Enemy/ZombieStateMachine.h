/**
 * EnemyStateMachine.h
 *
 * プレイヤーの状態遷移を行うステートマシン
 */
#pragma once
#include "src/Actor/StateMachine.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class Zombie;
			class ZombieStatus;


			/**
			 * ゾンビステートマシンクラス
			 */

			class ZombieStateMachine : public StateMachine
			{
			private:
				/** StateMachineを親クラスとする */
				using SuperClass = StateMachine;

				/** オーナー(ゾンビ) */
				Zombie* m_owner = nullptr;
				/** オーナーのステータス */
				ZombieStatus* m_ownerStatus = nullptr;


			public:
				/** コンストラクタ */
				ZombieStateMachine();
				/** デストラクタ */
				~ZombieStateMachine();

				/** 更新処理 */
				virtual void Update() override;


			public:
				/** 状態切り替え */
				void ChangeState();
				/** 近接攻撃状態に切り替えができるか */
				bool CanChangeToMeleeAttack()const;
				/** 歩き状態に切り替えができるか */
				bool CanChangeToWalkState() const;
				/** 初期設定を行う */
				void Setup(Zombie* zombie, ZombieStatus* zombieStatus);


			public:
				/**
				 * ゾンビ取得
				 * NOTE: 各Stateでのみ使用予定
				 */
				Zombie* GetOwner() { return m_owner; }
				/** 移動方向を設定 */
				void SetMoveDirection(const Vector3& direction);
				/** 移動方向を取得 */
				const Vector3& GetMoveDirection()const;
				/** 移動速度を取得 */
				float GetMoveSpeed()const;
				/** 攻撃力を取得 */
				uint16_t GetAttackPower()const;
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
			};
		}
	}
}


