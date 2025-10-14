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
				//スティック入力を取得
				auto* playerStateMachine = GetOwner<PlayerStateMachine>();
				const Vector3 direction = playerStateMachine->GetLStickDirection();
				const float power = playerStateMachine->GetLStickPower();

				//プレイヤーの移動速度を設定
				auto* player = playerStateMachine->GetOwner();
				const auto* status = player->GetStatus();
				const auto moveSpeed = status->GetMoveSpeed();
				player->SetSpeed(direction * power * moveSpeed);
			}


			void WalkState::Exit()
			{
				// 適用おわったで速度を0にする
				auto* playerStateMachine = GetOwner<PlayerStateMachine>();
				auto* player = playerStateMachine->GetOwner();
				player->SetSpeed(Vector3::Zero);
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