/**
 * ZombieState.h
 * 
 * ゾンビの各ステートの処理を行う
 */
#pragma once
#include "src/Actor/IState.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class ZombieStateMachine;


			/**
			 * 攻撃状態クラス
			 */
			class ZombieAttackState : public IState
			{
				appState(ZombieAttackState);


			private:
				/** 現在時間 */
				float m_currentTime = 0.0f;


			public:
				/** コンストラクタ */
				ZombieAttackState(ZombieStateMachine* owner);
				/** デストラクタ */
				~ZombieAttackState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 死亡状態クラス
			 */
			class ZombieDeathState : public IState
			{
				appState(ZombieDeathState);


			private:
				/** 現在の時間 */
				float m_currentTime = 0.0f;


			public:
				ZombieDeathState(ZombieStateMachine* owner);
				~ZombieDeathState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 起き上がり状態クラス
			 */
			class ZombieGetUpState : public IState
			{
				appState(ZombieGetUpState);


			public:
				ZombieGetUpState(ZombieStateMachine* owner);
				~ZombieGetUpState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 被弾状態クラス
			 */
			class ZombieHitState : public IState
			{
				appState(ZombieHitState);


			private:
				/** 現在の時間 */
				float m_currentTime = 0.0f;


			public:
				ZombieHitState(ZombieStateMachine* owner);
				~ZombieHitState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 待機状態クラス
			 */
			class ZombieIdleState : public IState
			{
				appState(ZombieIdleState);


			public:
				/** コンストラクタ */
				ZombieIdleState(ZombieStateMachine* owner);
				/** デストラクタ */
				~ZombieIdleState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/** 
			 * 歩行状態クラス 
			 */
			class ZombieWalkState : public IState
			{
				appState(ZombieWalkState);


			public:
				/** コンストラクタ */
				ZombieWalkState(ZombieStateMachine* owner);
				/** デストラクタ */
				~ZombieWalkState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};			
		}
	}
}