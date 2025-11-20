/**
 * PlayerState.h
 * 
 * プレイヤーの各ステートの処理を行う
 */
#include "src/Actor/IState.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			class PlayerStateMachine;


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