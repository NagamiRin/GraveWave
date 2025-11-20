/**
 * GameFlowManager.cpp
 *
 * インゲームの流れを管理するクラス
 */
#include "stdafx.h"
#include "GameFlowManager.h"
#include "src/Actor/Enemy/EnemySpawner.h"
#include "src/GameFlow/BattleFlow.h"
#include "src/GameFlow/PreparationFlow.h"
#include "src/GameFlow/ScoreCounter.h"
#include "src/Core/BattleManager.h"


namespace nsApp
{
    namespace nsFlow
    {
        GameFlowManager* GameFlowManager::m_instance = nullptr;


        GameFlowManager::GameFlowManager()
        {
            //各フェーズのクラスを生成
            nsFlow::BattleFlow::CreateInstance();
            nsFlow::PreparationFlow::CreateInstance();
            //スコアカウンターを生成
            nsFlow::ScoreCounter::CreateInstance();

            //todo for test
            m_currentPhase = EnInGameFlow::enBattle;
            nsFlow::BattleFlow::GetInstance()->SetInformation(m_waveCount);
        }


        GameFlowManager::~GameFlowManager()
        {
            //各フェーズのクラスを生成
            nsFlow::BattleFlow::DeleteInstance();
            nsFlow::PreparationFlow::DeleteInstance();
            //スコアカウンターを削除
            nsFlow::ScoreCounter::DeleteInstance();
        }


        void GameFlowManager::Update()
        {
            m_currentPhase;
            //各フェーズの更新処理
            nsFlow::BattleFlow::GetInstance()->Update();
            nsFlow::PreparationFlow::GetInstance()->Update();
            //スコアカウンターの更新処理
            nsFlow::ScoreCounter::GetInstance()->Update();
        }


        void GameFlowManager::SwitchNextPhase()
        {
            switch (m_currentPhase)
            {
                case EnInGameFlow::enPreparation:
                {
                    m_waveCount++;
                    nsFlow::BattleFlow::GetInstance()->SetInformation(m_waveCount);
                    m_currentPhase = EnInGameFlow::enBattle;
                    break;
                }
                case EnInGameFlow::enBattle:
                {
                    nsFlow::PreparationFlow::GetInstance()->SetInformation();
                    m_currentPhase = EnInGameFlow::enPreparation;
                    break;
                }
                default:
                {
                    break;
                }            
            }
        }


        bool GameFlowManager::IsClearConditions() const
        {
            // 全ウェーブが終わって敵を倒したか
            {
                if (m_waveCount == 2 && m_currentPhase == enPreparation) {
                    return true;
                }
            }

            return false;
        }
    }
}