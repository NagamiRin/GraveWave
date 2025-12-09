/**
 * PlayerState.h
 * 
 * プレイヤーの各ステートの処理を行う
 */
#pragma once
#include "src/Actor/IState.h"

namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			class GunBase;
		}
	}
}


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			class PlayerStateMachine;


			/**
			 * 武器切り替え状態のクラス
			 */
			class WeaponSwitchState : public IState
			{
				appState(WeaponSwitchState);


			private:
				enum EnSwitchStep
				{
					enSwitchStep_Out,		// 引っ込める
					enSwitchStep_Change,	// 切り替え
					enSwitchStep_In,		// 出す
				};


			private:
				/** 銃のポインタ */
				nsGun::GunBase* m_gun = nullptr;
				/** 現在の切り替え時間 */
				float m_currentSwitchTime = 0.0f;		
				/** 武器の切り替え中か */
				bool m_isSwitching = false;

				EnSwitchStep m_step = enSwitchStep_Out;


			public:
				/** コンストラクタ */
				WeaponSwitchState(PlayerStateMachine* owner);
				/** デストラクタ */
				~WeaponSwitchState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/** 
			 * 歩行状態のクラス 
			 */
			class WalkState : public IState
			{
				appState(WalkState);


			public:
				/** コンストラクタ */
				WalkState(PlayerStateMachine* owner);
				/** デストラクタ */
				~WalkState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 待機状態のクラス
			 */
			class IdleState : public IState
			{
				appState(IdleState);


			public:
				/** コンストラクタ */
				IdleState(PlayerStateMachine* owner);
				/** デストラクタ */
				~IdleState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};
		}		
	}
}