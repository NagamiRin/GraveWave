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
			 * 被弾状態クラス
			 */
			class BossHitState : public IState
			{
				appState(BossHitState);


			private:
				/** 現在のアニメーション時間 */
				float m_currentTime = 0.0f;

			public:
				/** コンストラクタ */
				BossHitState(BossStateMachine* owner);
				/** デストラクタ */
				~BossHitState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 死亡状態クラス
			 */
			class BossDeathState : public IState
			{
				appState(BossDeathState);


			private:
			public:
				/** コンストラクタ */
				BossDeathState(BossStateMachine* owner);
				/** デストラクタ */
				~BossDeathState();


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