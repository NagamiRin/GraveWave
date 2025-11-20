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
				m_stateMap.emplace(IdleState::ID(), new IdleState(this));
                m_stateMap.emplace(WalkState::ID(), new WalkState(this));
                m_stateMap.emplace(MeleeAttackState::ID(), new MeleeAttackState(this));
                m_stateMap.emplace(NotAppearState::ID(), new NotAppearState(this));
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
                if (m_ownerStatus->GetHP() <= 0.0f) {
                    m_requestStateId = NotAppearState::ID();
                    return;
                }
                else if (CanChangeToMeleeAttack()) {
                    m_requestStateId = MeleeAttackState::ID();
                    return;
                }
                else if (CanChangeToWalkState()) {
                    m_requestStateId = WalkState::ID();
                    return;
                }
                else {
					m_requestStateId = IdleState::ID();
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