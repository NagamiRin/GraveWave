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
			MeleeAttackState::MeleeAttackState(ZombieStateMachine* owner)
				:IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			MeleeAttackState::~MeleeAttackState()
			{
			}


			void MeleeAttackState::Enter()
			{
			}


			void MeleeAttackState::Update()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();

				m_currentCoolTime -= g_gameTime->GetFrameDeltaTime();
				if (m_currentCoolTime <= 0.0f) m_currentCoolTime = 0.0f;

				if (m_currentCoolTime == 0.0f) {
					nsCore::BattleManager::GetInstance()->DealingDamage(stateMachine->GetAttackPower());
					m_currentCoolTime = stateMachine->GetDealingDamage();
				}
			}


			void MeleeAttackState::Exit()
			{
			}


			/**********************************************************/


			WalkState::WalkState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			WalkState::~WalkState()
			{
			}


			void WalkState::Enter()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Back);
				stateMachine->SetDirection(Vector3::Back);
			}


			void WalkState::Update()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				const Vector3 moveAmount = stateMachine->GetMoveDirection() * stateMachine->GetMoveSpeed();

				stateMachine->SetPosition(stateMachine->GetPosition() + moveAmount);
			}


			void WalkState::Exit()
			{
				auto* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Zero);
			}


			/**********************************************************/


			IdleState::IdleState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;			
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


			/**********************************************************/


			NotAppearState::NotAppearState(ZombieStateMachine* owner)
				:IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			NotAppearState::~NotAppearState()
			{
			}


			void NotAppearState::Enter()
			{
			}


			void NotAppearState::Update()
			{
			}


			void NotAppearState::Exit()
			{
			}
		}
	}
}