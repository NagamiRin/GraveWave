/**
 * StateMachine.cpp
 *
 * ステートマシンの基底クラス
 */
#include "stdafx.h"
#include "StateMachine.h"
#include "src/Actor/IState.h"


namespace nsApp
{
    namespace nsActor
    {
        StateMachine::StateMachine()
        {
        }


        StateMachine::~StateMachine()
        {
        }


        void StateMachine::Update()
        {
            if (m_currentStateId != m_requestStateId)
            {
				IState* nextState = FindState(m_requestStateId);
                K2_ASSERT(nextState, "次の状態が見つからない");
                if (nextState) {
                    if (m_currentState) {
                        m_currentState->Exit();
                    }
                    nextState->Enter();
					m_currentState = nextState;
                }
                m_currentStateId = m_requestStateId;
            }
            if (m_currentState) {
                m_currentState->Update();
            }
        }
    }
}