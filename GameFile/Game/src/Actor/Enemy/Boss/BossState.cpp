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


namespace {
	constexpr float HIT_ANIMATION_INTERVAL = 2.0f;
	constexpr float ANIMATION_COMPLEMENT = 1.0f;
}

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
				Boss* owner = GetOwner<BossStateMachine>()->GetOwner();

				owner->PlayAnimation(EnAnimationVar_Throw, ANIMATION_COMPLEMENT);

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

				Boss* owner = GetOwner<BossStateMachine>()->GetOwner();
				owner->PlayAnimation(EnAnimationVar_Walk, ANIMATION_COMPLEMENT);
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
				Boss* owner = GetOwner<BossStateMachine>()->GetOwner();
				owner->PlayAnimation(EnAnimationVar_Idle, ANIMATION_COMPLEMENT);
			}


			void BossIdleState::Update()
			{
			}


			void BossIdleState::Exit()
			{
			}


			/**********************************************************/


			BossHitState::BossHitState(BossStateMachine* owner)
				:IState(owner)
			{
			}


			BossHitState::~BossHitState()
			{
			}


			void BossHitState::Enter()
			{
				auto* stateMachine = GetOwner<BossStateMachine>();

				Boss* owner = GetOwner<BossStateMachine>()->GetOwner();
				owner->PlayAnimation(EnAnimationVar_Hit, ANIMATION_COMPLEMENT);
				stateMachine->SetHitting(true);
				stateMachine->AddReactionNum();
			}


			void BossHitState::Update()
			{
				auto* stateMachine = GetOwner<BossStateMachine>();
				auto* owner = GetOwner<BossStateMachine>()->GetOwner();

				if (!owner->IsPlayAnimation()) {
					stateMachine->SetHitting(false);
				}
			}


			void BossHitState::Exit()
			{
				auto* stateMachine = GetOwner<BossStateMachine>();

				stateMachine->SetHitting(false);
			}


			/**********************************************************/


			BossDeathState::BossDeathState(BossStateMachine* owner)
				:IState(owner)
			{
			}


			BossDeathState::~BossDeathState()
			{
			}


			void BossDeathState::Enter()
			{
				Boss* owner = GetOwner<BossStateMachine>()->GetOwner();
				owner->PlayAnimation(EnAnimationVar_Death, ANIMATION_COMPLEMENT);
			}


			void BossDeathState::Update()
			{
				Boss* owner = GetOwner<BossStateMachine>()->GetOwner();

				if (!owner->IsPlayAnimation())
				{
					owner->Destruction();
				}
			}


			void BossDeathState::Exit()
			{
			}
}
	}
}