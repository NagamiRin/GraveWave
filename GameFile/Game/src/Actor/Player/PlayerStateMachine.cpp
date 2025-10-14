/**
 * PlayerStateMachine.cpp
 *
 * プレイヤーの状態遷移を行うステートマシン
 */
#include "stdafx.h"
#include "src/Actor/StateMachine.h"
#include "src/Actor/Player/PlayerStateMachine.h"
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
                if (CanChangeToWalkState()) {
                    m_requestStateId = WalkState::ID();
                }

                else {
					m_requestStateId = IdleState::ID();
                }           
            }


            bool PlayerStateMachine::CanChangeToWalkState() const 
            {
                if (fabsf(GetLStickPower()) >= FLT_EPSILON) {
                   
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