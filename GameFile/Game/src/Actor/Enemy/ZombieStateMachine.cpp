/**
 * ZombieStateMachine.cpp
 *
 * ゾンビの状態遷移を行うステートマシン
 */
#include "stdafx.h"
#include "ZombieStateMachine.h"
#include "src/Actor/StateMachine.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Enemy/ZombieStatus.h"
#include "src/Actor/Enemy/ZombieState.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            ZombieStateMachine::ZombieStateMachine()
            {
				m_stateMap.emplace(ZombieIdleState::ID(), new ZombieIdleState(this));
                m_stateMap.emplace(ZombieWalkState::ID(), new ZombieWalkState(this));
                m_stateMap.emplace(ZombieMeleeAttackState::ID(), new ZombieMeleeAttackState(this));
            }


            ZombieStateMachine::~ZombieStateMachine()
            {
            }


            void ZombieStateMachine::Update()
            {
                ChangeState();

                SuperClass::Update();
            }


            void ZombieStateMachine::ChangeState()
            {
                if (CanChangeToMeleeAttack()) {
                    m_requestStateId = ZombieMeleeAttackState::ID();
                    return;
                }
                else if (CanChangeToWalkState()) {
                    m_requestStateId = ZombieWalkState::ID();
                    return;
                }
                else {
					m_requestStateId = ZombieIdleState::ID();
                }
            }


            bool ZombieStateMachine::CanChangeToMeleeAttack()const
            {
                if (m_owner->GetLocalPosition().z == m_owner->GetStopPosition()) return true;
                else return false;
            }


            bool ZombieStateMachine::CanChangeToWalkState() const
            {
                const float wallDistance = m_owner->GetPosition().z - m_owner->GetPlayerPosition().z;
                if (wallDistance >= 0.0f)return true;
                else return false;
            }


            void ZombieStateMachine::Setup(Zombie* owner, ZombieStatus* ownerStatus)
            {
				m_owner = owner;
                m_ownerStatus = ownerStatus;
            }


            void ZombieStateMachine::SetMoveDirection(const Vector3& direction)
            {
                m_owner->SetMoveDirection(direction);
            }


            const Vector3& ZombieStateMachine::GetMoveDirection() const
            {
                return m_owner->GetMoveDirection();
            }


            float ZombieStateMachine::GetMoveSpeed()const
            {
                return m_ownerStatus->GetMoveSpeed();
            }


            uint16_t ZombieStateMachine::GetAttackPower()const
            {
                return m_ownerStatus->GetAttackPower();
            }


            float ZombieStateMachine::GetDealingDamage()const
            {
                return m_ownerStatus->GetAttackFrequency();
            }


            void ZombieStateMachine::SetPosition(const Vector3& position)
            {
                m_owner->SetLocalPosition(position);
            }


            const Vector3& ZombieStateMachine::GetPosition()const
            {
                return m_owner->GetPosition();
            }


            void ZombieStateMachine::SetDirection(const Vector3& direction)
            {
                m_owner->SetDirection(direction);
            }


            const Vector3& ZombieStateMachine::GetPlayerPosition() const
            {
                return m_owner->GetPlayerPosition();
            }
        }
    }
}