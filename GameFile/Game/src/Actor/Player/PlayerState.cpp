/**
 * PlayerState.cpp
 *
 * プレイヤーの各ステートの処理を行う
 */
#include "stdafx.h"
#include "src/Actor/Player/Player.h"
#include "src/Actor/Player/PlayerState.h"
#include "src/Actor/Player/PlayerStateMachine.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			WalkState::WalkState(PlayerStateMachine* owner)
				: IState(owner)
			{
			}


			WalkState::~WalkState()
			{
			}


			void WalkState::Enter()
			{

			}


			void WalkState::Update()
			{
				auto* playerStateMachine = GetOwner<PlayerStateMachine>();
				auto* player = playerStateMachine->GetOwner();
				auto* status = player->GetStatus();
				const float moveSpeed = status->GetMoveSpeed();
				const Vector3 playerPosition = player->GetLocalPosition();
				//X方向のスティック入力量を取得
				const float InputAmount = playerStateMachine->GetLStickXDirAmount();
				//プレイヤーを移動させる
				if (InputAmount >= 0.0f) {
					//右方向
					player->SetLocalPosition(Vector3(playerPosition.x + (InputAmount * moveSpeed), playerPosition.y, playerPosition.z));
				}
				else {
					//左方向
					player->SetLocalPosition(Vector3(playerPosition.x + (InputAmount * moveSpeed), playerPosition.y, playerPosition.z));
				}
			}


			void WalkState::Exit()
			{;
			}



			/**********************************************************/


			IdleState::IdleState(PlayerStateMachine* owner)
				: IState(owner)
			{
			}


			IdleState::~IdleState()
			{
			}


			void IdleState::Enter()
			{
			}


			void IdleState::Update() 
			{
			}


			void IdleState::Exit()
			{
			}
		}		
	}
}