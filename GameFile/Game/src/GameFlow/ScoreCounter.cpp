/**
 * ScoreCounter.cpp
 *
 * スコアを集計するクラス
 */
#include "stdafx.h"
#include "ScoreCounter.h"
#include "src/Core/ParameterManager.h"


namespace nsApp
{
    namespace nsFlow
    {
        ScoreCounter* ScoreCounter::m_instance = nullptr;


        ScoreCounter::ScoreCounter()
        {
            ParameterManager::Get().LoadParameter<MasterScoreParameter>("Assets/Parameter/ScoreParameter.json", [](const nlohmann::json& j, MasterScoreParameter& p)
                {
                    p.m_eliminateZombieScore = j["EliminateZombieScore"].get<uint8_t>();
                });

            auto* param = ParameterManager::Get().GetParameter<MasterScoreParameter>();

            m_eliminateZombieScore = param->m_eliminateZombieScore;
        }


        ScoreCounter::~ScoreCounter()
        {
        }


        void ScoreCounter::Update()
        {
        }
    }
}