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
				/** 経過時間 */
				float m_currentTime = 0.0f;


			public:
				ZombieAttackState(ZombieStateMachine* owner);
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
				/** 経過時間 */
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
				/** 経過時間 */
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
				ZombieIdleState(ZombieStateMachine* owner);
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


			private:
				/** エフェクト生成の経過時間 */
				float m_elapsedTime = 0.0f;


			public:
				ZombieWalkState(ZombieStateMachine* owner);
				~ZombieWalkState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};			
		}
	}
}