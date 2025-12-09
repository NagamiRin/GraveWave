/**
 * BossState.h
 * 
 * ボスの各ステートの処理を行う
 */
#pragma once
#include "src/Actor/IState.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class BossStateMachine;
			

			/**
			 * 投石状態クラス
			 */
			class BossThrowState : public IState
			{
				appState(BossThrowState);


			public:
				/** コンストラクタ */
				BossThrowState(BossStateMachine* owner);
				/** デストラクタ */
				~BossThrowState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/** 
			 * 歩行状態クラス 
			 */
			class BossWalkState : public IState
			{
				appState(BossWalkState);


			public:
				/** コンストラクタ */
				BossWalkState(BossStateMachine* owner);
				/** デストラクタ */
				~BossWalkState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 待機状態クラス
			 */
			class BossIdleState : public IState
			{
				appState(BossIdleState);


			public:
				/** コンストラクタ */
				BossIdleState(BossStateMachine* owner);
				/** デストラクタ */
				~BossIdleState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};			
		}		
	}
}