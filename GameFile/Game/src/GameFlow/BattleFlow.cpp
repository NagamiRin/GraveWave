/**
 * BattleFlow.cpp
 *
 * 戦闘フェーズの処理
 */
#include "stdafx.h"
#include "BattleFlow.h"
#include "src/Actor/Enemy/EnemySpawner.h"
#include "src/Core/ParameterManager.h"
#include "src/Core/BattleManager.h"
#include "src/GameFlow/GameFlowManager.h"


namespace nsApp
{
    namespace nsFlow
    {
        BattleFlow* BattleFlow::m_instance = nullptr;


        BattleFlow::BattleFlow()
        {
            //ゾンビ出現のウェーブ情報を読み込み
            ParameterManager::Get().LoadParameter<MasterWaveParameter>("Assets/Parameter/WaveParameter.json", [](const nlohmann::json& j, MasterWaveParameter& p)
                {
                    p.m_leftCount = j["LeftCount"].get<uint16_t>();
                    p.m_centerCount = j["CenterCount"].get<uint16_t>();
                    p.m_rightCount = j["RightCount"].get<uint16_t>();
                    p.m_isBossSpawn = j["BossSpawn"].get<bool>();
                    p.m_spawnInterval = j["SpawnInterval"].get<float>();
                });
        }


        BattleFlow::~BattleFlow()
        {
            //パラメーター削除
            ParameterManager::Get().UnloadParameter< MasterWaveParameter>();
        }


        void BattleFlow::Update()
        {
            if (nsFlow::GameFlowManager::GetInstance()->m_currentPhase != enBattle)return;

            m_currentTime -= g_gameTime->GetFrameDeltaTime();
            if (m_currentTime < 0.0f) m_currentTime = 0.0f;

            EnemySpawn();
            ChangeNextPhase();
            m_eliminateEnemyNum;
        }


        void BattleFlow::SetInformation(uint8_t waveCount)
        {
            const auto& paramList = ParameterManager::Get().GetParameters<MasterWaveParameter>();
            auto param = paramList.at(waveCount - 1);

            m_spawnCountList[enSpwnerType_Left] = param->m_leftCount;
            m_spawnCountList[enSpwnerType_Center] = param->m_centerCount;
            m_spawnCountList[enSpwnerType_Right] = param->m_rightCount;
            m_isBossSpawn = param->m_isBossSpawn;
            m_spawnInterval = param->m_spawnInterval;

            m_waveEnemyNum = m_spawnCountList[enSpwnerType_Left] + m_spawnCountList[enSpwnerType_Center] + m_spawnCountList[enSpwnerType_Right];
            m_remainingEnemiesNum = m_waveEnemyNum;
            m_eliminateEnemyNum;

            //ウェーブのタイプをセット
            if (m_isBossSpawn) m_waveType = enWaveType_Boss;
            else m_waveType = enWaveType_Normal;
        }


        void BattleFlow::EnemySpawn()
        {
            //通常ウェーブ
            if (m_waveType == enWaveType_Normal) {


                if (m_remainingEnemiesNum == 0 || m_currentTime > 0.0f) {
                    return;
                }
                uint8_t selectSpawner = rand() % enSpwnerType_None;
                // 対象の場所が出るまで繰り返す
                uint8_t count = m_spawnCountList[selectSpawner];
                if (count == 0) {
                    // 既に生成できない状態なら適当な場所からとってくる
                    for (int type = enSpwnerType_Left; type < enSpwnerType_None; ++type) {
                        if (selectSpawner != type) {
                            selectSpawner = type;
                            count = m_spawnCountList[selectSpawner];
                            if (count >= 1) {
                                break;
                            }
                        }
                    }
                }

                auto* spawner = nsCore::BattleManager::GetInstance()->GetEnemySpawner(static_cast<EnSpwnerType>(selectSpawner));

                spawner->ZombieCreate();                

                m_currentTime = m_spawnInterval;
                m_remainingEnemiesNum--;
            }
            //ボスウェーブ
            else if (m_waveType == enWaveType_Boss) {
                //ボスを出現
                if (m_isBossSpawn && !m_isSpawnBoss) {
                    auto* spawner = nsCore::BattleManager::GetInstance()->GetEnemySpawner(static_cast<EnSpwnerType>(enSpwnerType_Center));
                    spawner->BossCreate();
                    m_isSpawnBoss = true;
                }

                //ボスの生存中は継続的にゾンビを出現
                if (nsCore::BattleManager::GetInstance()->IsBossAlive() || m_currentTime > 0.0f) {
                    return;
                }
                uint8_t selectSpawner = rand() % enSpwnerType_None;
                if (selectSpawner == enSpwnerType_Center) selectSpawner = enSpwnerType_Right;
                // 対象の場所が出るまで繰り返す
                uint8_t count = m_spawnCountList[selectSpawner];
                if (count == 0) {
                    // 既に生成できない状態なら適当な場所からとってくる
                    for (int type = enSpwnerType_Left; type < enSpwnerType_None; ++type) {
                        if (selectSpawner != type) {
                            selectSpawner = type;
                            count = m_spawnCountList[selectSpawner];
                            if (count >= 1) {
                                break;
                            }
                        }
                    }
                }

                auto* spawner = nsCore::BattleManager::GetInstance()->GetEnemySpawner(static_cast<EnSpwnerType>(selectSpawner));

                spawner->ZombieCreate();
                m_waveEnemyNum++;
                m_currentTime = m_spawnInterval;
            }
        }


        void BattleFlow::ChangeNextPhase()
        {
            if (m_eliminateEnemyNum != m_waveEnemyNum) return;
            nsFlow::GameFlowManager::GetInstance()->SwitchNextPhase();
            m_eliminateEnemyNum = 0;
            m_isSpawnBoss = false;
        }
    }
}