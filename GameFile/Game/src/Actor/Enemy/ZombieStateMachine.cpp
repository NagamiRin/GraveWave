/**
 * ZombieStateMachine.cpp
 *
 * ゾンビの状態遷移を行うステートマシン
 */
#include "stdafx.h"
#include "ZombieStateMachine.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Enemy/ZombieState.h"
#include "src/Actor/Enemy/ZombieStatus.h"
#include "src/Actor/StateMachine.h"



namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            ZombieStateMachine::ZombieStateMachine()
            {
                //各状態のID、インスタンスをセット
                m_stateMap.emplace(ZombieAttackState::ID(), new ZombieAttackState(this));
                m_stateMap.emplace(ZombieDeathState::ID(),  new ZombieDeathState(this));
                m_stateMap.emplace(ZombieGetUpState::ID(),  new ZombieGetUpState(this));
                m_stateMap.emplace(ZombieHitState::ID(),    new ZombieHitState(this));
				m_stateMap.emplace(ZombieIdleState::ID(),   new ZombieIdleState(this));
                m_stateMap.emplace(ZombieWalkState::ID(),   new ZombieWalkState(this));
            }


            ZombieStateMachine::~ZombieStateMachine()
            {
            }


            void ZombieStateMachine::Update()
            {
                //状態切り替え
                ChangeState();

                //親クラスの更新
                SuperClass::Update();
            }


            void ZombieStateMachine::ChangeState()
            {
                //各状態に遷移していく
                //優先順位が高いものから

                if (CanChangeToDeath()) {           //死亡状態
                    m_requestStateId = ZombieDeathState::ID();
                    return;
                }
                else if (CanChangeToHit()) {        //被弾状態
                    m_requestStateId = ZombieHitState::ID();
                    return;
                }
                else if (CanChangeToGetUp()) {      //起き上がり状態
                    m_requestStateId = ZombieGetUpState::ID();
                    return;
                }
                else if (CanChangeToAttack()) {     //攻撃状態
                    m_requestStateId = ZombieAttackState::ID();
                    return;
                }
                else if (CanChangeToWalk()) {       //歩行状態
                    m_requestStateId = ZombieWalkState::ID();
                    return;
                }
                else {                              //待機状態
					m_requestStateId = ZombieIdleState::ID();
                }
            }


            bool ZombieStateMachine::CanChangeToDeath() const
            {
                //HPが全損したなら
                if (m_ownerStatus->GetHP() <= 0) {
                    return true;
                }

                return false;
            }


            bool ZombieStateMachine::CanChangeToHit() const
            {
                //オーナー（ゾンビ）が被弾したなら
                if (m_owner->IsHit()) {
                    return true;
                }

                return false;
            }


            bool ZombieStateMachine::CanChangeToGetUp() const
            {
                if (m_isStanding) return true;

                return false;
            }


            bool ZombieStateMachine::CanChangeToAttack()const
            {
                //攻撃フラグがたっているなら
                if (m_owner->IsAttackState()) return true;

               return false;
            }


            bool ZombieStateMachine::CanChangeToWalk() const
            {
                //壁との距離が一定以上離れているなら
                const float wallDistance = m_owner->GetPosition().z - m_owner->GetPlayerPosition().z;
                if (wallDistance >= 0.0f)return true;
                else return false;
            }


            void ZombieStateMachine::Setup(Zombie* owner, ZombieStatus* ownerStatus)
            {
                //持ち主（ゾンビ）と持ち主のステータスをセット
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