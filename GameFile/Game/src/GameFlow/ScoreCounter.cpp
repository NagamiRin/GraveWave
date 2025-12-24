/**
 * ScoreCounter.cpp
 *
 * スコアを集計するクラス
 */
#include "stdafx.h"
#include "ScoreCounter.h"
#include "src/Core/ParameterManager.h"
#include "src/Core/BattleManager.h"


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

            m_scoreVar.emplace(enScoreType_EliminateZombie, param->m_eliminateZombieScore);
        }


        ScoreCounter::~ScoreCounter()
        {
        }


        void ScoreCounter::Update()
        {
        }


        void ScoreCounter::AddScore(const EnScoreType type)
        {
            uint16_t add = m_scoreVar.find(type)->second;

            m_score += add;
            nsCore::BattleManager::GetInstance()->AddMoney(add);
        }
    }
}