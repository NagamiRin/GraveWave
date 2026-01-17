/**
 * EnemySpawner.cpp
 *
 * エネミースポナークラス
 */
#include "stdafx.h"
#include "EnemySpawner.h"
#include "src/Actor/Enemy/Boss/Boss.h"
#include "src/Actor/Enemy/EnemyPoolManager.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Core/ParameterManager.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {            
            EnemySpawner::EnemySpawner(EnSpwnerType type)
            {
                //管理クラスから読み込んだパラメーターをもらう
                const auto& param = ParameterManager::Get().GetParameter<MasterSpawnerParameter>(type);

                //読み込んだパラメーターをセット
                m_maxXPosition = param->m_maxXPosition;
                m_minXPosition = param->m_minXPosition;
                m_spawnPositionZ = param->m_spawnPositionZ;

                //このスポナーの基点となるスポーン位置をセット
                const float posX = m_minXPosition + (m_maxXPosition - m_minXPosition);
                m_baseSpawnPosition = Vector3(posX, 0.0f, m_spawnPositionZ);
            }


            EnemySpawner::~EnemySpawner()
            {                            
            }
            

            void EnemySpawner::ZombieCreate()
            {
                //プールから使用可能なゾンビを探す
                auto* zombie = EnemyPoolManager::GetInstance()->FindUse();

                //オブジェクトをアクティブに
                zombie->Activate();

                //ゾンビの初期化
                zombie->Initialize(DecideSpawnPosition());
            }


            void EnemySpawner::BossCreate()
            {
                //ボスを取得
                auto* boss = EnemyPoolManager::GetInstance()->GetBoss();

                //ボスを出現させる
                boss->Initialize(m_baseSpawnPosition);
                boss->Activate();

                //ボスを使用中に
                EnemyPoolManager::GetInstance()->UseToBoss();
            }


            Vector3 EnemySpawner::DecideSpawnPosition()
            {
                //横方向のスポーン位置はランダムにする
                float besideRange = m_maxXPosition - m_minXPosition;
                float result = rand() % (static_cast<uint16_t>(besideRange));
                float besidePos = result + m_minXPosition;

                //スポーン位置を返す
                return Vector3(besidePos, 0.0f, m_spawnPositionZ);
            }
        }
    }
}