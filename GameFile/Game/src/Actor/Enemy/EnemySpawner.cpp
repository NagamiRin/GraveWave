/**
 * EnemySpawner.cpp
 *
 * エネミースポナークラス
 */
#include "stdafx.h"
#include "src/Actor/Enemy/EnemySpawner.h"

#include "src/Actor/Enemy/Zombie.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            EnemySpawner::EnemySpawner(uint8_t MaxEnemyNum, float baseSpawnPosition, Vector3 spawnPosition)
                :m_baseSpawnTime(baseSpawnPosition),
                m_spawnPosition(spawnPosition)
            {
                m_zombiePool.reserve(MaxEnemyNum);
                for (int i = 0; i < MaxEnemyNum; ++i) {
                    PoolInformation<Zombie> info;
                    info.m_enemy = NewGO<Zombie>(enGameObjectPriority_Default, "Zombie");
                    info.m_enemy->Deactivate();   // プールに溜めるだけなのでアクティブではない状態にしておく
                    info.m_canUse = true;
                    m_zombiePool.push_back(info);
                }
            }


            EnemySpawner::~EnemySpawner()
            {
                for (auto& info : m_zombiePool) {
                    if (info.m_enemy != nullptr) {
                        DeleteGO(info.m_enemy);
                    }
                }
                
            }


            Zombie* EnemySpawner::Create()
            {
                if (m_spawnCoolTime > 0.0f) {
                    return nullptr;
                }

                PoolInformation<Zombie>* info = nullptr;
                for (auto& search : m_zombiePool) {
                    if (search.m_canUse) {
                        info = &search;
                        break;
                    }
                }

                if (info == nullptr) {
                    // プールが埋まっていて使えない
                    return nullptr;
                }

                info->m_canUse = false;
                auto* zombie = info->m_enemy;
                zombie->Activate();
                zombie->Initialize(m_spawnPosition);
                //生成時間をセット
                m_spawnCoolTime = m_baseSpawnTime;

                return zombie;
            }


            void EnemySpawner::Delete(Zombie* target)
            {
                PoolInformation<Zombie>* info = nullptr;
                for (auto& search : m_zombiePool) {
                    if (search.m_enemy = target) {
                        info = &search;
                        break;
                    }
                }

                info->m_canUse = true;
                // 破棄処理を呼びたい
                target->Destruction();
                info->m_enemy->Deactivate();
            }
        }
    }
}