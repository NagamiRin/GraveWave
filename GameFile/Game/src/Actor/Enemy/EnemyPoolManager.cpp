/**
 * EnemyPoolManager.cpp
 *
 * エネミーのプールを管理
 */
#include "stdafx.h"
#include "EnemyPoolManager.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Core/BattleManager.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {            
            EnemyPoolManager* EnemyPoolManager::m_instance = nullptr;


            EnemyPoolManager::EnemyPoolManager()
            {                
            }


            EnemyPoolManager::~EnemyPoolManager()
            {
                for (auto& info : m_zombiePool) {
                    if (info.m_enemy != nullptr) {

                        //フィールドに出ているエネミーのコリジョンを削除する
                        CleaningUp();

                        DeleteGO(info.m_enemy);                        
                    }
                }
            }


            void EnemyPoolManager::CleaningUp()
            {
                for (auto& search : m_zombiePool) {
                    search.m_enemy->Destruction();
                }
            }


            void EnemyPoolManager::SetUp(uint16_t maxEnemyNum)
            {
                m_zombiePool.reserve(maxEnemyNum);
                for (int i = 0; i < maxEnemyNum; ++i) {
                    PoolInformation<Zombie> info;
                    info.m_enemy = NewGO<Zombie>(enGameObjectPriority_Default, "Zombie");
                    info.m_enemy->SetStopPosition(nsCore::BattleManager::GetInstance()->GetEnemyStopPosition());
                    info.m_enemy->Deactivate();   // プールに溜めるだけなのでアクティブではない状態にしておく
                    info.m_canUse = true;
                    m_zombiePool.push_back(info);
                }
            }


            EnemyPoolManager::PoolInformation<Zombie>* EnemyPoolManager::FindInformation()
            {
                for (auto& search : m_zombiePool) {
                    if (search.m_canUse) {
                        return &search;
                    }
                }
                return nullptr;
            }
            

            Zombie* EnemyPoolManager::FindUse()
            {
                auto* targetInformation = FindInformation();
                if (targetInformation == nullptr) {
                    return nullptr;
                }
                targetInformation->m_canUse = false;

                // 使ってるエネミー一覧に追加
                m_usedEnemyList.push_back(targetInformation->m_enemy);

                return targetInformation->m_enemy;
            }


            void EnemyPoolManager::Restore(Zombie* target)
            {
                PoolInformation<Zombie>* info = nullptr;
                for (auto& search : m_zombiePool) {
                    if (search.m_enemy = target) {
                        info = &search;
                        break;
                    }
                }

				// 使っているエネミー一覧から削除
                for(auto it = m_usedEnemyList.begin(); it != m_usedEnemyList.end(); ++it) {
                    if (*it == target) {
                        m_usedEnemyList.erase(it);
                        break;
                    }
				}

                info->m_canUse = true;
                target->Destruction();
                info->m_enemy->Deactivate();
            }


            void EnemyPoolManager::ForEachUsedEnemy(const std::function<void(Zombie*)>& func)
            {
                for (auto* enemy : m_usedEnemyList) {
                    func(enemy);
                }
            }
        }
    }
}