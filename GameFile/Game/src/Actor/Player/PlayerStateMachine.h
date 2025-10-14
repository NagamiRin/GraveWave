/**
 * PlayerStateMachine.h
 *
 * プレイヤーの状態遷移を行うステートマシン
 */
#pragma once
#include "src/Actor/StateMachine.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			class Player;
			class WalkState;


			/**
			 * プレイヤーステートマシンクラス
			 */

			class PlayerStateMachine : public nsActor::StateMachine
			{
				/** StateMachineを親クラスとする */
				using SuperClass = nsActor::StateMachine;

			private:
				/** オーナー(プレイヤー) */
				Player* m_owner = nullptr;
				/** Lスティックの入力方向 */
				Vector3 m_LStickDirection = Vector3::Zero;
				/** Lスティックの入力量 */
				float m_inputPower = 0.0f;


			public:
				/** コンストラクタ */
				PlayerStateMachine();
				/** デストラクタ */
				~PlayerStateMachine();

				/** 更新処理 */
				virtual void Update() override;


			public:
				/** 状態切り替え */
				void ChangeState();
				/** 歩き状態に切り替えができるか */
				bool CanChangeToWalkState() const;
				/** 初期設定を行う */
				void Setup(Player* player);


			public:
				/**
				 * プレイヤー取得
				 * NOTE: 各Stateでのみ使用予定
				 */
				Player* GetOwner() { return m_owner; }


			public:
				/** Lスティックの入力方向を設定 */
				inline void SetLStickDirection(const Vector3& direction) { m_LStickDirection = direction; }
				/** Lスティックの入力方向を取得 */
				inline const Vector3& GetLStickDirection() const { return m_LStickDirection; }
				/** Lスティックの入力量を設定 */
				inline void SetLStickPower(float power) { m_inputPower = power; }
				/** Lスティックの入力量を取得 */
				inline const float GetLStickPower() const { return m_inputPower; }
			};
		}
	}
}


