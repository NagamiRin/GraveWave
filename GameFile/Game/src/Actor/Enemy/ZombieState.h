/**
 * ZombieState.h
 * 
 * ゾンビの各ステートの処理を行う
 */
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
			class MeleeAttackState : public IState
			{
				appState(MeleeAttackState);


			private:
				/** 残りの攻撃のクールタイム */
				float m_currentCoolTime = 0.0f;


			public:
				/** コンストラクタ */
				MeleeAttackState(ZombieStateMachine* owner);
				/** デストラクタ */
				~MeleeAttackState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/** 
			 * 歩行状態クラス 
			 */
			class WalkState : public IState
			{
				appState(WalkState);


			public:
				/** コンストラクタ */
				WalkState(ZombieStateMachine* owner);
				/** デストラクタ */
				~WalkState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 待機状態クラス
			 */
			class IdleState : public IState
			{
				appState(IdleState);


			public:
				/** コンストラクタ */
				IdleState(ZombieStateMachine* owner);
				/** デストラクタ */
				~IdleState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};


			/*********************************/


			/**
			 * 非出現状態クラス
			 */
			class NotAppearState : public IState
			{
				appState(NotAppearState);


			public:
				/** コンストラクタ */
				NotAppearState(ZombieStateMachine* owner);
				/** デストラクタ */
				~NotAppearState();


			public:
				void Enter() override;
				void Update() override;
				void Exit() override;
			};
		}		
	}
}