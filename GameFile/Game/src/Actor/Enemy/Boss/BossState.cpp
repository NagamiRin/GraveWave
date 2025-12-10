/**
 * BossState.cpp
 *
 * ボスの各ステートの処理を行う
 */
#include "stdafx.h"
#include "BossState.h"
#include "src/Actor/Enemy/Boss/Boss.h"
#include "src/Actor/Enemy/Boss/BossStateMachine.h"
#include "src/Core/BattleManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			BossThrowState::BossThrowState(BossStateMachine* owner)
				: IState(owner)
			{
				m_owner = GetOwner<BossStateMachine>();
			}


			BossThrowState::~BossThrowState()
			{
				
			}


			void BossThrowState::Enter()
			{
				BossStateMachine* stateMachine = GetOwner<BossStateMachine>();

				stateMachine->GetOwner()->ThrowStone(stateMachine->GetPosition(), Vector3(0.0f, 100.0f, 500.0f));
			}


			void BossThrowState::Update()
			{
				BossStateMachine* stateMachine = GetOwner<BossStateMachine>();

			}


			void BossThrowState::Exit()
			{
				auto* stateMachine = GetOwner<BossStateMachine>();


			}


			/**********************************************************/


			BossWalkState::BossWalkState(BossStateMachine* owner)
				: IState(owner) 
			{
				m_owner = GetOwner<BossStateMachine>();
			}


			BossWalkState::~BossWalkState()
			{
			}


			void BossWalkState::Enter()
			{
				BossStateMachine* stateMachine = GetOwner<BossStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Back);
				stateMachine->SetDirection(Vector3::Back);
			}


			void BossWalkState::Update()
			{
				BossStateMachine* stateMachine = GetOwner<BossStateMachine>();
				const Vector3 moveAmount = stateMachine->GetMoveDirection() * stateMachine->GetMoveSpeed();

				stateMachine->SetPosition(stateMachine->GetPosition() + moveAmount);
			}


			void BossWalkState::Exit()
			{
				auto* stateMachine = GetOwner<BossStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Zero);
			}


			/**********************************************************/


			BossIdleState::BossIdleState(BossStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;			
			}


			BossIdleState::~BossIdleState()
			{
			}


			void BossIdleState::Enter()
			{
			}


			void BossIdleState::Update()
			{
			}


			void BossIdleState::Exit()
			{
			}
		}
	}
}