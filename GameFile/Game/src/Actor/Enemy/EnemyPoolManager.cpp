/**
 * EnemyPoolManager.cpp
 *
 * エネミーのプールを管理
 */
#include "stdafx.h"
#include "EnemyPoolManager.h"
#include "src/Actor/Enemy/Boss/Boss.h"
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
                //プールのゾンビを走査
                for (auto& info : m_zombiePool) {
                    if (info.m_enemy) {

                        //コリジョンを削除
                        CleaningUp();

                        //エネミー削除
                        DeleteGO(info.m_enemy);                        
                    }
                }

                //ボス削除
                DeleteGO(m_boss.m_enemy);
            }


            void EnemyPoolManager::Update()
            {
                //HPがなくなったゾンビをプールに戻す
                Restore();
                //HPがなくなったボスをプールに戻す
                ReturnBoss();
            }


            void EnemyPoolManager::CleaningUp()
            {
                //ゾンビの破棄処理
                for (auto& search : m_zombiePool) {
                    search.m_enemy->Destruction();
                }
            }


            void EnemyPoolManager::ReturnBoss()
            {
                //ボスのHP
                const float bossHp = m_boss.m_enemy->GetStatus()->GetHP();

                //ボスの破棄処理
                if (bossHp <= 0.0f && !m_boss.m_canUse) {
                    RestoreBoss();
                }
            }


            void EnemyPoolManager::SetUp(uint16_t maxEnemyNum)
            {
                //ゾンビの最大数分、メモリを確保
                m_zombiePool.reserve(maxEnemyNum);

                //ゾンビたちをnew
                for (int i = 0; i < maxEnemyNum; ++i) {
                    PoolInformation<Zombie> info;
                    info.m_enemy = NewGO<Zombie>(enGameObjectPriority_Enemy, "Zombie");

                    // プールに溜めるだけなのでアクティブではない状態にしておく
                    info.m_enemy->Deactivate();   

                    //使用可能にする
                    info.m_canUse = true;

                    //プールの配列に追加
                    m_zombiePool.push_back(info);
                }

                //ボスをnew
                m_boss.m_enemy = NewGO<Boss>(enGameObjectPriority_Enemy, "Boss");
                m_boss.m_enemy->Deactivate();
                m_boss.m_canUse = true;
            }


            EnemyPoolManager::PoolInformation<Zombie>* EnemyPoolManager::FindInformation()
            {
                //使用可能なゾンビをプールから走査する
                for (auto& search : m_zombiePool) {
                    if (search.m_canUse) {
                        return &search;
                    }
                }
                return nullptr;
            }
            

            Zombie* EnemyPoolManager::FindUse()
            {
                //使用可能なゾンビを取得
                auto* targetInformation = FindInformation();

                //ポインタがnullなら実行しない（一応）
                if (targetInformation == nullptr) {
                    return nullptr;
                }

                //使用不可にする
                targetInformation->m_canUse = false;

                //使ってるエネミー一覧に追加
                m_usedEnemyList.push_back(targetInformation->m_enemy);

                //利用可能なエネミーのポインタを返す
                return targetInformation->m_enemy;
            }    


            void EnemyPoolManager::Restore()
            {
                //ゾンビの構造体
                PoolInformation<Zombie>* info = nullptr;

                //HPがなくなっているゾンビを走査
                for (auto& search : m_zombiePool) {
                    if (search.m_enemy->CanRestore()) {
                        info = &search;
                        break;
                    }                    
                }                

                //ポインタがnullなら実行しない
                if (!info) return;

                // 使っているエネミー一覧から削除
                for (auto it = m_usedEnemyList.begin(); it != m_usedEnemyList.end(); ++it) {
                    if (*it == info->m_enemy) {
                        m_usedEnemyList.erase(it);
                        break;
                    }
                }

                //使用可能に
                info->m_canUse = true;

                //破棄処理
                info->m_enemy->Destruction();

                //オブジェクトを非アクティブに
                info->m_enemy->Deactivate();

                //プール帰還のフラグを戻す
                info->m_enemy->SetRestore(false);

                //ゾンビを倒した報告
                nsCore::BattleManager::GetInstance()->ReportEliminateZombie();
            }


            void EnemyPoolManager::RestoreBoss()
            {
                //使用可能に
                m_boss.m_canUse = true;
            }


            void EnemyPoolManager::ForEachUsedEnemy(const std::function<void(Zombie*)>& func)
            {
                //使用中のエネミーから走査
                for (auto* enemy : m_usedEnemyList) {
                    func(enemy);
                }
            }
        }
    }
}