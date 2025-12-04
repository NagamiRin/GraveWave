/**
 * PlayerState.cpp
 *
 * プレイヤーの各ステートの処理を行う
 */
#include "stdafx.h"
#include "src/Actor/Player/Player.h"
#include "src/Actor/Player/PlayerState.h"
#include "src/Actor/Player/PlayerStateMachine.h"
#include "src/Actor/Gun/GunBase.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			WeaponSwitchState::WeaponSwitchState(PlayerStateMachine* owner)
				: IState(owner)
			{

			}


			WeaponSwitchState::~WeaponSwitchState()
			{

			}

			void WeaponSwitchState::Enter()
			{
				auto* playerStateMachine = GetOwner<PlayerStateMachine>();
				playerStateMachine->SetSwitchingWeapon(true);
				m_gun = playerStateMachine->GetOwner()->GetGun();
				m_currentSwitchTime = 0.0f;
				m_step = enSwitchStep_Out;
			}

			void WeaponSwitchState::Update()
			{
				switch (m_step)
				{
					case enSwitchStep_Out:
					{
						// 仕舞うアニメーション再生
						if (m_gun->IsEquipment()) {
							m_gun->PutGun();
						} 
						else {
							m_step = enSwitchStep_Change;
						}
						break;
					}
					case enSwitchStep_Change:
					{
						// 新しい銃の生成(中で破棄もしてる)
						m_gun = GetOwner<PlayerStateMachine>()->GetOwner()->ChangeGun();
						// 銃を持つアニメーション再生開始
						m_step = enSwitchStep_In;
						break;
					}
					case enSwitchStep_In:
					{
						if (!m_gun->IsEquipment()) {
							m_gun->TakeOutGun();
						}
						else {
							auto* playerStateMachine = GetOwner<PlayerStateMachine>();
							playerStateMachine->SetSwitchingWeapon(false);
						}
						break;
					}
				}
			}

			void WeaponSwitchState::Exit()
			{

			}


			/**********************************************************/


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