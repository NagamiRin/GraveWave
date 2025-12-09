/**
 * ZombieState.cpp
 *
 * ゾンビの各ステートの処理を行う
 */
#include "stdafx.h"
#include "ZombieState.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Enemy/ZombieStateMachine.h"
#include "src/Core/BattleManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			ZombieMeleeAttackState::ZombieMeleeAttackState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			ZombieMeleeAttackState::~ZombieMeleeAttackState()
			{
			}


			void ZombieMeleeAttackState::Enter()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Back);
				stateMachine->SetDirection(Vector3::Back);
			}


			void ZombieMeleeAttackState::Update()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				const Vector3 moveAmount = stateMachine->GetMoveDirection() * stateMachine->GetMoveSpeed();

				stateMachine->SetPosition(stateMachine->GetPosition() + moveAmount);
			}


			void ZombieMeleeAttackState::Exit()
			{
				auto* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Zero);
			}


			/**********************************************************/


			ZombieWalkState::ZombieWalkState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			ZombieWalkState::~ZombieWalkState()
			{
			}


			void ZombieWalkState::Enter()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Back);
				stateMachine->SetDirection(Vector3::Back);
			}


			void ZombieWalkState::Update()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				const Vector3 moveAmount = stateMachine->GetMoveDirection() * stateMachine->GetMoveSpeed();

				stateMachine->SetPosition(stateMachine->GetPosition() + moveAmount);
			}


			void ZombieWalkState::Exit()
			{
				auto* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Zero);
			}


			/**********************************************************/


			ZombieIdleState::ZombieIdleState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;			
			}


			ZombieIdleState::~ZombieIdleState()
			{
			}


			void ZombieIdleState::Enter()
			{
			}


			void ZombieIdleState::Update()
			{
			}


			void ZombieIdleState::Exit()
			{
			}			
		}
	}
}