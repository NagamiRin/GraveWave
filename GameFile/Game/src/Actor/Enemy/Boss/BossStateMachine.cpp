/**
 * BossStateMachine.cpp
 *
 * ボスの状態遷移を行うステートマシン
 */
#include "stdafx.h"
#include "BossStateMachine.h"
#include "src/Actor/StateMachine.h"
#include "src/Actor/Enemy/Boss/Boss.h"
#include "src/Actor/Enemy/Boss/BossStatus.h"
#include "src/Actor/Enemy/Boss/BossState.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            BossStateMachine::BossStateMachine()
            {
                m_stateMap.emplace(BossThrowState::ID(), new BossThrowState(this));
				m_stateMap.emplace(BossIdleState::ID(), new BossIdleState(this));
                m_stateMap.emplace(BossWalkState::ID(), new BossWalkState(this));
            }


            BossStateMachine::~BossStateMachine()
            {
            }


            void BossStateMachine::Update()
            {
                ChangeState();

                SuperClass::Update();
            }


            void BossStateMachine::ChangeState()
            {
                if (CanChangeToThrowState()) {
                    m_requestStateId = BossThrowState::ID();
                    return;
                }
                else if (CanChangeToWalkState()) {
                    m_requestStateId = BossWalkState::ID();
                    return;
                }
                else {
					m_requestStateId = BossIdleState::ID();
                }
            }


            bool BossStateMachine::CanChangeToThrowState() const
            {
                if (m_owner->GetLocalPosition().z <= m_ownerStatus->GetAttackRange()) {
                    return true;
                }
                return false;
            }

                        
            bool BossStateMachine::CanChangeToWalkState() const
            {
                const float wallDistance = m_owner->GetPosition().z - m_owner->GetPlayerPosition().z;
                if (wallDistance >= 0.0f) return true;
                else return false;
            }


            void BossStateMachine::Setup(Boss* owner, BossStatus* ownerStatus)
            {
				m_owner = owner;
                m_ownerStatus = ownerStatus;
            }


            void BossStateMachine::SetMoveDirection(const Vector3& direction)
            {
                m_owner->SetMoveDirection(direction);
            }


            const Vector3& BossStateMachine::GetMoveDirection() const
            {
                return m_owner->GetMoveDirection();
            }


            float BossStateMachine::GetMoveSpeed()const
            {
                return m_ownerStatus->GetMoveSpeed();
            }


            uint16_t BossStateMachine::GetAttackPower()const
            {
                return m_ownerStatus->GetAttackPower();
            }


            float BossStateMachine::GetAttackRange() const
            {
                return m_ownerStatus->GetAttackRange();
            }


            float BossStateMachine::GetDealingDamage()const
            {
                return m_ownerStatus->GetAttackFrequency();
            }


            void BossStateMachine::SetPosition(const Vector3& position)
            {
                m_owner->SetLocalPosition(position);
            }


            const Vector3& BossStateMachine::GetPosition()const
            {
                return m_owner->GetPosition();
            }


            void BossStateMachine::SetDirection(const Vector3& direction)
            {
                m_owner->SetDirection(direction);
            }


            const Vector3& BossStateMachine::GetPlayerPosition() const
            {
                return m_owner->GetPlayerPosition();
            }
        }
    }
}