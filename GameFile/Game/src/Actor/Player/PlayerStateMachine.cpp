/**
 * PlayerStateMachine.cpp
 *
 * プレイヤーの状態遷移を行うステートマシン
 */
#include "stdafx.h"
#include "PlayerStateMachine.h"
#include "src/Actor/StateMachine.h"
#include "src/Actor/Player/Player.h"
#include "src/Actor/Player/PlayerState.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsPlayer
        {
            PlayerStateMachine::PlayerStateMachine()
            {
				m_stateMap.emplace(IdleState::ID(), new IdleState(this));
                m_stateMap.emplace(WalkState::ID(), new WalkState(this));
                m_stateMap.emplace(WeaponSwitchState::ID(), new WeaponSwitchState(this));
            }


            PlayerStateMachine::~PlayerStateMachine()
            {
            }


            void PlayerStateMachine::Update()
            {
                ChangeState();

                SuperClass::Update();
            }


            void PlayerStateMachine::ChangeState()
            {
                if (CanChangeToWeaponSwitchState()) m_requestStateId = WeaponSwitchState::ID();
                else if (CanChangeToWalkState())  m_requestStateId = WalkState::ID();                
                else m_requestStateId = IdleState::ID();
            }


            bool PlayerStateMachine::CanChangeToWeaponSwitchState() const
            {
                //todo for test
                if (IsSwitchingWeapon()) {
                    return true;
                }
                return false;
            }


            bool PlayerStateMachine::CanChangeToWalkState() const 
            {
                if (fabsf(GetLStickXDirAmount()) >= FLT_EPSILON) {                   
                    return true;
                }
                return false;
            }


            void PlayerStateMachine::Setup(Player* owner)
            {
				m_owner = owner;
            }
        }
    }
}