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
#include "src/Core/ModelLOD.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			namespace
			{
				struct ZombieCallback : public btCollisionWorld::RayResultCallback
				{
					bool isHit = false;
					btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
					{
						// Enemyじゃない&&Gohstじゃない なら当たらない
						if (rayResult.m_collisionObject->getUserIndex() != nsApp::enCollision_Wall && rayResult.m_collisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT) {
							return rayResult.m_hitFraction;
						}
						isHit = true;
						return rayResult.m_hitFraction;
					}
				};
			}

			ZombieAttackState::ZombieAttackState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			ZombieAttackState::~ZombieAttackState()
			{
			}


			void ZombieAttackState::Enter()
			{
			}


			void ZombieAttackState::Update()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				float frequency = owner->GetStatus()->GetAttackFrequency();

				m_currentTime += g_gameTime->GetFrameDeltaTime();
				if (m_currentTime >= frequency) {
					owner->SetAttack(true);
					owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Attack);
					m_currentTime = 0.0f;
				}
			}


			void ZombieAttackState::Exit()
			{
				auto* stateMachine = GetOwner<ZombieStateMachine>();
			}


			/**********************************************************/


			ZombieDeathState::ZombieDeathState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieDeathState::~ZombieDeathState()
			{
			}


			void ZombieDeathState::Enter()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Death);
			}


			void ZombieDeathState::Update()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();

				m_currentTime += g_gameTime->GetFrameDeltaTime();
				//todo 後で定数
				if (m_currentTime >= 4.0f) owner->SetRestore(true);
			}


			void ZombieDeathState::Exit()
			{
			}


			/**********************************************************/


			ZombieGetUpState::ZombieGetUpState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieGetUpState::~ZombieGetUpState()
			{
			}


			void ZombieGetUpState::Enter()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_GetUp);
			}


			void ZombieGetUpState::Update()
			{
			}


			void ZombieGetUpState::Exit()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
			}


			/**********************************************************/


			ZombieHitState::ZombieHitState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieHitState::~ZombieHitState()
			{
			}


			void ZombieHitState::Enter()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Hit);
			}


			void ZombieHitState::Update()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				m_currentTime += g_gameTime->GetFrameDeltaTime();

				//todo 後で定数に
				if (m_currentTime >= 2.0f) {
					owner->SetHit(false);
				}
			}


			void ZombieHitState::Exit()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();

				m_currentTime = 0.0f;
				owner->SetHit(false);
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
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Idle);
			}


			void ZombieIdleState::Update()
			{
			}


			void ZombieIdleState::Exit()
			{
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

				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Walk);
			}


			void ZombieWalkState::Update()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				auto* ownerStatus = owner->GetStatus();

				const Vector3 moveAmount = stateMachine->GetMoveDirection() * stateMachine->GetMoveSpeed();

				stateMachine->SetPosition(stateMachine->GetPosition() + moveAmount);

				//レイを飛ばして、壁に当たったら攻撃状態に移行させる
				{
					Vector3 startPos = owner->GetLocalPosition();
					Vector3 endPos = owner->GetLocalPosition() + (owner->GetDirection() * ownerStatus->GetMoveSpeed());
					ZombieCallback cb;
					bool isHit = PhysicsWorld::GetInstance()->RayTest(startPos, endPos, cb, [](const btCollisionWorld::RayResultCallback* result)
						{
							const auto* resultCB = dynamic_cast<const ZombieCallback*>(result);
							if (resultCB->isHit) {
								return true;
							}
							return false;
						});
					// 攻撃させる
					owner->SetAttackState(true);
				}
			}


			void ZombieWalkState::Exit()
			{
				auto* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Zero);

				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->SetAttackState(false);
			}			
		}
	}
}