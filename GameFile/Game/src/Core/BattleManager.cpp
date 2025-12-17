/**
 * BattleManager.cpp
 *
 * 戦闘全体を管理するクラス
 */
#include "stdafx.h"
#include "BattleManager.h"
#include "src/Actor/BackGround/BackGround.h"
#include "src/Actor/Bullet/BulletManager.h"
#include "src/Actor/Player/Player.h"
#include "src/Actor/Enemy/EnemyManager.h"
#include "src/Actor/Enemy/EnemyPoolManager.h"
#include "src/Actor/Enemy/EnemySpawner.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Gun/GunBase.h"
#include "src/Battle/Inventory.h"
#include "src/Battle/Shop.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ParameterManager.h"
#include "src/Core/SaveData.h"
#include "src/Camera/GameCamera.h"
#include "src/GameFlow/GameFlowManager.h"
#include "src/GameFlow/BattleFlow.h"
#include "src/GameFlow/PreparationFlow.h"
#include "src/GameFlow/ScoreCounter.h"
#include "src/UI/InGameUIManager.h"
#include "src/Actor/Wall/Wall.h"


namespace nsApp
{
    namespace nsCore {

        namespace
        {
            struct CrosshairCallback : public btCollisionWorld::RayResultCallback
            {
                bool isHit = false;
                btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
                {
                    // Enemyじゃない&&Gohstじゃない なら当たらない
                    if (rayResult.m_collisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT) {
                        return rayResult.m_hitFraction;
                    }
                    if (rayResult.m_collisionObject->getUserIndex() != nsApp::enCollision_Enemy && rayResult.m_collisionObject->getUserIndex() != nsApp::enCollision_Stone) {
                        return rayResult.m_hitFraction;
                    }
                    
                    isHit = true;
                    return rayResult.m_hitFraction;
                }
            };
        }

        BattleManager* BattleManager::m_instance = nullptr;


        BattleManager::BattleManager()
        {
            //インゲーム共通のパラメーターを読み込み
            ParameterManager::Get().LoadParameter<MasterBattleParameter>("Assets/Parameter/BattleParameter.json", [](const nlohmann::json& j, MasterBattleParameter& p)
                {
                    p.m_maxEnemyNum = j["MaxEnemyNum"].get<uint8_t>();           
                    p.m_clearWaveNum = j["ClearWaveNum"].get<uint8_t>();
                    p.m_verticalLimitAngle = j["VerticalLimitAngle"].get<float>();
                    p.m_horizontalLimitAngle = j["HorizontalLimitAngle"].get<float>();
                    p.m_gravityAmount = j["GravityAmount"].get<float>();
                    p.m_enemyStopPosition = j["EnemyStopPosition"].get<float>();
                });

            auto* battleParam = ParameterManager::Get().GetParameter<MasterBattleParameter>();
            m_enemyStopPosition = battleParam->m_enemyStopPosition;

            //スポナーのパラメーターを読み込み
            ParameterManager::Get().LoadParameter<MasterSpawnerParameter>("Assets/Parameter/SpawnerParameter.json", [](const nlohmann::json& j, MasterSpawnerParameter& p)
                {
                    p.m_minPos = j["MinPos"].get<float>();
                    p.m_maxPos = j["MaxPos"].get<float>();
                    p.m_spawnPositionZ = j["SpawnPositionZ"].get<float>();
                });            

            //ゾンビのプールマネージャーを生成
            nsApp::nsActor::nsEnemy::EnemyPoolManager::CreateInstance();
            nsApp::nsActor::nsEnemy::EnemyPoolManager::GetInstance()->SetUp(battleParam->m_maxEnemyNum);

            //位置ごとのスポナーを生成
            const auto& paramList = ParameterManager::Get().GetParameters<MasterSpawnerParameter>();
            for (int i = 0; i < paramList.size(); ++i) {
                m_enemySpawner[i] = std::make_unique<nsActor::nsEnemy::EnemySpawner>(static_cast<EnSpwnerType>(i));
            }

            //ヒット判定のマネージャーを生成
            m_hitManagerObject = NewGO<CollisionHitManagerObject>(enGameObjectPriority_HitManager, "CollisionHitManagerObject");

            //弾管理のマネージャーを生成
			nsActor::nsBullet::BulletManager::CreateInstance();

            //ショップを生成
			nsBattle::Shop::CreateInstance();

            //背景を生成
            m_backGround = NewGO<nsActor::nsBackGround::BackGround>(enGameObjectPriority_BackGround, "BackGround");

            //防壁を生成
            m_wall = NewGO<nsActor::nsWall::Wall>(enGameObjectPriority_Wall, "Wall");

            //プレイヤーを生成
            m_player = NewGO<nsActor::nsPlayer::Player>(enGameObjectPriority_Player, "Player");

            //インベントリを生成
            nsBattle::Inventory::CreateInstance();

            //ゲームカメラを生成
            m_camera = NewGO<nsCamera::GameCamera>(enGameObjectPriority_Camera, "GameCamera");

            //ゲーム進行のマネージャーを生成
            nsFlow::GameFlowManager::CreateInstance();
        }


        BattleManager::~BattleManager()
        {
            //パラメーターを削除
            ParameterManager::Get().UnloadParameter<MasterBattleParameter>();            
            //ゾンビのプールマネージャーを削除
            nsApp::nsActor::nsEnemy::EnemyPoolManager::DeleteInstance();
            //弾管理のマネージャーを削除
            nsActor::nsBullet::BulletManager::DeleteInstance();
            //背景を削除
            DeleteGO(m_backGround);
            //防壁を削除
            DeleteGO(m_wall);
            //プレイヤーを削除
            DeleteGO(m_player);
            //インベントリを削除
            nsBattle::Inventory::DeleteInstance();
            //ショップを削除
            nsBattle::Shop::DeleteInstance();
            //ゲームカメラ削除
            DeleteGO(m_camera);
            //ゲーム進行のマネージャーを削除
            nsFlow::GameFlowManager::DeleteInstance();
            //ヒット判定のマネージャーを削除
            DeleteGO(m_hitManagerObject);
        }


        void BattleManager::Update()
        {
            CollisionHitManager::Get().Update();
            //ゲーム進行のマネージャーの更新処理
            nsFlow::GameFlowManager::GetInstance()->Update();
            //ショップの更新処理
            nsBattle::Shop::GetInstance().Update();
			//弾管理マネージャーの更新処理
			nsActor::nsBullet::BulletManager::GetInstance()->Update();
            //エネミーのプールの更新処置
            nsActor::nsEnemy::EnemyPoolManager::GetInstance()->Update();

            //壁への攻撃処理
            DealingDamage();

            UpdateCameraForPlayer();

            // @todo for test
            // この関数を呼ぶ場所を後で用意
            LateUpdate();


            for (auto* notify : m_notifyList)
            {
                switch (notify->m_notifyType)
                {
                    case nsBattle::enNotifyType_BuyGun:
                    {
                        const auto* buyGunNotify = static_cast<const nsApp::nsBattle::BuyGunNotify*>(notify);

                        nsBattle::Inventory::GetInstance().SetMainWeaponID(buyGunNotify->m_gunID);
                        break;
                    }
                }
            }
        }


        void BattleManager::LateUpdate()
        {
            //クロスヘア
            {
                CrossHairNotify* crossHairNotify = new CrossHairNotify();                

                // レイの処理
                {
                    Vector3 startPos = m_camera->GetCameraPos();
                    Vector3 endPos = m_camera->GetCameraPos() + (m_camera->GetCameraDir() * 3000.0f);
                    CrosshairCallback cb;
                    bool isHit = PhysicsWorld::GetInstance()->RayTest(startPos, endPos, cb, [](const btCollisionWorld::RayResultCallback* result)
                        {
                            const auto* resultCB = dynamic_cast<const CrosshairCallback*>(result);
                            if (resultCB->isHit) {
                                return true;
                            }
                            return false;
                        });
                    // 赤色にする
                    crossHairNotify->m_isAiming = isHit;
                }

                if (CollisionHitManager::Get().IsHit()) {
                    crossHairNotify->m_isHit = true;
                    CollisionHitManager::Get().ResetHit();
                }
                else crossHairNotify->m_isHit = false;

                nsUI::InGameUIManager::GetInstance()->AddNotify(crossHairNotify);

                //delete crossHairNotify;
            }

            // 弾数
            {
                const uint8_t remainingAmmo = m_player->GetGun()->GetRemainingAmmo();
                const uint8_t maxAmmo = m_player->GetGun()->GetMaxAmmo();
                const std::string& gunName = m_player->GetGun()->GetGunName();

                RemainingBulletsNotify* remainingBulletsNotify = new RemainingBulletsNotify();
                remainingBulletsNotify->m_remainingNum = remainingAmmo;
                remainingBulletsNotify->m_maxNum = maxAmmo;
                remainingBulletsNotify->m_gunName = gunName;                

                nsUI::InGameUIManager::GetInstance()->AddNotify(remainingBulletsNotify);

                //delete remainingBulletsNotify;
            }

            //リロード
            {
                const float reloadTime = m_player->GetGun()->GetReloadTime();
                const float currentReloadTime = m_player->GetGun()->GetCurrentReloadTime();

                ReloadingNotify* reloadingNotify = new ReloadingNotify();
                reloadingNotify->m_reloadTime = reloadTime;
                reloadingNotify->m_currentReloadTime = currentReloadTime;

                nsUI::InGameUIManager::GetInstance()->AddNotify(reloadingNotify);
            }

            //スコア
            {
                const uint16_t score = nsApp::nsFlow::ScoreCounter::GetInstance()->GetScore();

                ScoreNotify* scoreNotify = new ScoreNotify();
                scoreNotify->m_score = score;

                nsUI::InGameUIManager::GetInstance()->AddNotify(scoreNotify);

                // セーブデータにスコアを設定
                SaveData::Get().SetScore(score);

                //delete scoreNotify;
            }

            //エネミーの残数
            {
                const uint8_t remainingEnemy = nsFlow::BattleFlow::GetInstance()->GetRemainingEnemy();

                RemainingEnemiesNotify* remainingEnemiesNotify = new RemainingEnemiesNotify();
                remainingEnemiesNotify->m_remainingEnemy = remainingEnemy;

                nsUI::InGameUIManager::GetInstance()->AddNotify(remainingEnemiesNotify);

               //delete remainingEnemiesNotify;
            }

            // ミニマップ
            {
                nsApp::nsActor::nsEnemy::EnemyPoolManager::GetInstance()->ForEachUsedEnemy([&](nsActor::nsEnemy::Zombie* zombie)
                    {
                        EnemiesNotify* enemiesNotify = new EnemiesNotify();
                        enemiesNotify->m_iconId = reinterpret_cast<uintptr_t>(zombie);// ポインタのアドレスを uint64_t に変換
                        enemiesNotify->m_id = zombie->ID();
                        enemiesNotify->m_position = zombie->GetPosition();

                        nsUI::InGameUIManager::GetInstance()->AddNotify(enemiesNotify);

                        //delete enemiesNotify;
                    });               
            }

            //警告表示
            {
                nsApp::nsActor::nsEnemy::EnemyPoolManager::GetInstance()->ForEachUsedEnemy([&](nsActor::nsEnemy::Zombie* zombie)
                    {
                        CaveatNotify* caveatNotify = new CaveatNotify();
                        //todo for test
                        if (zombie->GetLocalPosition().z <= 300.0f) {
                            caveatNotify->m_caveatId = reinterpret_cast<uintptr_t>(zombie);// ポインタのアドレスを uint64_t に変換
                            caveatNotify->m_id = zombie->ID();
                            caveatNotify->m_position = zombie->GetPosition();

                            nsUI::InGameUIManager::GetInstance()->AddNotify(caveatNotify);
                        }
                        
                        //delete enemiesNotify;
                    });
            }

            //防壁のHP
            {
                const uint16_t maxWallHP = m_wall->GetMaxDurability();
                const uint16_t wallHP = m_wall->GetDurability();

                WallHPNotify* wallHPNotify = new WallHPNotify();
                wallHPNotify->m_maxWallHP = maxWallHP;
                wallHPNotify->m_wallHP = wallHP;

                nsUI::InGameUIManager::GetInstance()->AddNotify(wallHPNotify);

                //delete wallHPNotify;
            }

            //カウントダウン            
            {
                const float specifiedSeconds = nsFlow::PreparationFlow::GetInstance()->GetSpecifiedSeconds();
                const float currentCount = nsFlow::PreparationFlow::GetInstance()->GetCurrentCount();
                const bool isDrawCount = nsFlow::PreparationFlow::GetInstance()->IsDrawCount();

                CountdownNotify* countdownNotify = new CountdownNotify();
                countdownNotify->m_specifiedSeconds = specifiedSeconds;
                countdownNotify->m_currentSeconds = currentCount;
                countdownNotify->m_isDrawCount = isDrawCount;

                nsUI::InGameUIManager::GetInstance()->AddNotify(countdownNotify);

                //delete countdownNotify;
            }

            //ショップ
            {
                const int8_t menuIndex = nsBattle::Shop::GetInstance().GetMenuIndex();
                const bool isOpen = nsBattle::Shop::GetInstance().IsOpenMenu();

                ShopNotify* shopNotify = new ShopNotify();
                shopNotify->m_menuIndex = menuIndex;
                shopNotify->m_isOpen = isOpen;

                nsUI::InGameUIManager::GetInstance()->AddNotify(shopNotify);
            }

            //フェーズ切り替えのメッセージ
            {
                const uint8_t currentPhase = nsFlow::GameFlowManager::GetInstance()->GetGameFlow();

                PhaseSwitchNotify* phaseSwitchNotify = new PhaseSwitchNotify();
                phaseSwitchNotify->m_currentPhase = nsFlow::GameFlowManager::GetInstance()->GetGameFlow();
                phaseSwitchNotify->m_waveNum = nsFlow::GameFlowManager::GetInstance()->GetWaveCount();

                nsUI::InGameUIManager::GetInstance()->AddNotify(phaseSwitchNotify);
            }

        }

        
        void BattleManager::UpdateCameraForPlayer()
        {
            //カメラ座標を設定
            m_camera->SetCameraPos(m_player->GetPosition());
            //カメラの向きを設定
            m_camera->SetCameraDir(m_player->GetDirection());
        }


        void BattleManager::DeleteBoss()
        {
            nsApp::nsActor::nsEnemy::EnemyPoolManager::GetInstance()->RestoreBoss();
        }


        void BattleManager::ReportEliminateZombie()
        {
            //倒した敵を加算
            nsApp::nsFlow::BattleFlow::GetInstance()->AddEliminateEnemy();
            //スコア加算
            nsApp::nsFlow::ScoreCounter::GetInstance()->AddScoreEliminateZombie();
        }


        float BattleManager::GetVerLimitAngle()
        {
            auto* parameter = ParameterManager::Get().GetParameter<MasterBattleParameter>();

            return parameter->m_verticalLimitAngle;
        }


        float BattleManager::GetHorLimitAngle()
        {
            auto* parameter = ParameterManager::Get().GetParameter<MasterBattleParameter>();

            return parameter->m_horizontalLimitAngle;
        }


        float BattleManager::GetGravityAmount()
        {
            auto* parameter = ParameterManager::Get().GetParameter<MasterBattleParameter>();

            return parameter->m_gravityAmount;
        }


        bool BattleManager::IsBossAlive()
        {
            nsActor::nsEnemy::EnemyPoolManager::GetInstance()->IsBossAlive();

            return false;
        }


        float BattleManager::GetEnemyStopPosition()
        {
            auto* param = ParameterManager::Get().GetParameter<MasterBattleParameter>();
            return param->m_enemyStopPosition;
        }


        void BattleManager::DealingDamage()
        {
            const auto& enemyList = nsActor::nsEnemy::EnemyPoolManager::GetInstance()->GetUsedEnemyList();
            for (auto* enemy : enemyList) {
                if (enemy->IsAttack()) {
                    m_wall->ReduceDurability(enemy->GetStatus()->GetAttackPower());
                    enemy->SetAttack(false);
                }
            }
        }


        bool BattleManager::IsBattleFinish()const
        {
            if (IsBattleWin()) return true;
            if (IsBattleLose())return true;
            
            return false;
        }


        bool BattleManager::IsBattleWin()const
        {
            return nsFlow::GameFlowManager::GetInstance()->IsClearConditions();
        }

       
        bool BattleManager::IsBattleLose()const
        {
            return m_wall->CheckDestroyWall();
        }


        const std::vector<uint32_t>& BattleManager::GetSubWeaponIDList() const
        {
            return nsBattle::Inventory::GetInstance().GetSubWeaponID();
        }      


        const std::vector<uint32_t>& BattleManager::GetMainWeaponIDList() const
        {
			return nsBattle::Inventory::GetInstance().GetMainWeaponID();
        }


        void BattleManager::SetSubWeaponID(const uint32_t gunID)
        {
			nsBattle::Inventory::GetInstance().SetSubWeaponID(gunID);
        }


        void BattleManager::SetMainWeaponID(const uint32_t gunID)
        {
            nsBattle::Inventory::GetInstance().SetMainWeaponID(gunID);
        }


        void BattleManager::RequestChangeWeapon(const uint32_t weaponID)
        {
			m_player->RequestChangeGun(weaponID);
        }
    }
}