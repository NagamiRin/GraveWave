/**
 * EnemySpawner.cpp
 *
 * エネミースポナークラス
 */
#include "stdafx.h"
#include "EnemySpawner.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Enemy/Boss/Boss.h"
#include "src/Core/ParameterManager.h"
#include "src/Actor/Enemy/EnemyPoolManager.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {            
            EnemySpawner::EnemySpawner(EnSpwnerType type)
            {
                const auto& param = ParameterManager::Get().GetParameter<MasterSpawnerParameter>(type);
                m_maxPos = param->m_maxPos;
                m_minPos = param->m_minPos;
                m_spawnPositionZ = param->m_spawnPositionZ;

                const float posX = m_minPos + (m_maxPos - m_minPos);
                m_baseSpawnPosition = Vector3(posX, 0.0f, m_spawnPositionZ);
            }


            EnemySpawner::~EnemySpawner()
            {                            
            }
            

            void EnemySpawner::ZombieCreate()
            {
                auto* zombie = EnemyPoolManager::GetInstance()->FindUse();
                zombie->Activate();
                zombie->Initialize(DecideSpawnPosition());
            }


            void EnemySpawner::BossCreate()
            {
                auto* boss = EnemyPoolManager::GetInstance()->GetBoss();
                boss->Initialize(m_baseSpawnPosition);
                boss->Activate();
            }


            Vector3 EnemySpawner::DecideSpawnPosition()
            {
                float besideRange = m_maxPos - m_minPos;
                float result = rand() % (static_cast<uint16_t>(besideRange));
                float besidePos = result + m_minPos;

                return Vector3(besidePos, 0.0f, m_spawnPositionZ);
            }
        }
    }
}