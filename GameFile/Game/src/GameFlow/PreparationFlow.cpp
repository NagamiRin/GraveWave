/**
 * PreparationFlow.cpp
 *
 * 準備フェーズの処理
 */
#include "stdafx.h"
#include "PreparationFlow.h"
#include "src/GameFlow/GameFlowManager.h"
#include "src/Core/ParameterManager.h"


namespace nsApp
{
    namespace nsFlow
    {
        PreparationFlow* PreparationFlow::m_instance = nullptr;


        PreparationFlow::PreparationFlow()
        {
            ParameterManager::Get().LoadParameter<MasterPreparationParameter>("Assets/Parameter/PreparationParameter.json", [](const nlohmann::json& j, MasterPreparationParameter& p)
                {
                    p.m_toCountDownTime = j["ToCountdownTime"].get<float>();
                    p.m_specifiedSeconds = j["CountdownTime"].get<float>();
                });

            const auto& param = ParameterManager::Get().GetParameter<MasterPreparationParameter>();
            m_toCountDownTime = param->m_toCountDownTime;
            m_specifiedSeconds = param->m_specifiedSeconds;
        }


        PreparationFlow::~PreparationFlow()
        {
            ParameterManager::Get().UnloadParameter<MasterPreparationParameter>();
        }


        void PreparationFlow::Update()
        {
            if (nsFlow::GameFlowManager::GetInstance()->m_currentPhase != enPreparation)return;

            m_currentCount -= g_gameTime->GetFrameDeltaTime();
            if (m_currentCount <= 0.0f)m_currentCount = 0.0f;

            ChangeNextPhase();
        }


        void PreparationFlow::SetInformation()
        {
            m_currentCount = m_specifiedSeconds;
            m_isDrawCount = true;
        }


        void PreparationFlow::ChangeNextPhase()
        {
            if (m_currentCount > 0.0f) return;
            nsFlow::GameFlowManager::GetInstance()->SwitchNextPhase();
            m_isDrawCount = false;
        }
    }
}