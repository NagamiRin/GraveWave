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
			class WeaponSwitchState;


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
				/** LスティックのX方向の入力量 */
				float m_InputLStickXDir = 0.0f;

				/** 武器を切り替え中か */
				bool m_isSwitchingWeapon = false;


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
				/** 武器切り替え状態に切り替えができるか */
				bool CanChangeToWeaponSwitchState() const;
				/** 初期設定を行う */
				void Setup(Player* player);


			public:
				/**
				 * プレイヤー取得
				 * NOTE: 各Stateでのみ使用予定
				 */
				Player* GetOwner() { return m_owner; }


			public:
				/** LスティックのX方向の入力量を設定 */
				inline void SetLStickXDirAmount(const float direction) { m_InputLStickXDir = direction; }
				/** LスティックのX方向の入力量を取得 */
				inline const float GetLStickXDirAmount() const { return m_InputLStickXDir; }


			public:
				/** 武器を切り替え中かを設定 */
				inline void SetSwitchingWeapon(const bool isSwitching) { m_isSwitchingWeapon = isSwitching; }
				/** 武器を切り替え中かを取得 */
				inline const bool IsSwitchingWeapon() const { return m_isSwitchingWeapon; }
			};
		}
	}
}


