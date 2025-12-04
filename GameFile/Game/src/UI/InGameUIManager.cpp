/**
 * InGameUIManager.cpp
 *
 * インゲーム中のUIを管理するクラス
 */
#include "stdafx.h"
#include "InGameUIManager.h"
#include "src/UI/Crosshair.h"
#include "src/UI/CountdownUI.h"
#include "src/UI/RemainingBulletsUI.h"
#include "src/UI/ScoreUI.h"
#include "src/UI/ShopUI.h"
#include "src/UI/RemainingEnemyUI.h"
#include "src/UI/WallHPUI.h"
#include "src/UI/MiniMapUI.h"


namespace nsApp
{
    namespace nsUI
    {
        InGameUIManager* InGameUIManager::m_instance = nullptr;


        InGameUIManager::InGameUIManager()
        {
            //クロスヘアを生成
            m_crosshairUI = NewGO<Crosshair>(enGameObjectPriority_UI, "Crosshair");
            //カウントダウンUIを生成
            m_countdownUI = NewGO<CountdownUI>(enGameObjectPriority_UI, "CountdownUI");
            //残段数UIを生成
            m_remainingBulletsUI = NewGO<RemainingBulletsUI>(enGameObjectPriority_UI, "RemainingBulletsUI");
            //スコアUIを生成
            m_scoreUI = NewGO<ScoreUI>(enGameObjectPriority_UI, "ScoreUI");
            //敵の残数UIを生成
            m_remainingEnemyUI = NewGO<RemainingEnemyUI>(enGameObjectPriority_UI, "RemainingEnemyUI");
            //防壁のHPバーを生成
            m_wallHPUI = NewGO<WallHPUI>(enGameObjectPriority_UI, "WallHPUI");
            //ミニマップ生成
            m_miniMapUI = NewGO<MiniMapUI>(enGameObjectPriority_UI, "MiniMap");
            //ショップ生成
			m_shopUI = NewGO<ShopUI>(enGameObjectPriority_UI, "ShopUI");
        }


        InGameUIManager::~InGameUIManager()
        {
            DeleteGO(m_crosshairUI);
            DeleteGO(m_countdownUI);
            DeleteGO(m_remainingBulletsUI);
            DeleteGO(m_scoreUI);
            DeleteGO(m_remainingEnemyUI);
            DeleteGO(m_wallHPUI);
            DeleteGO(m_miniMapUI);
			DeleteGO(m_shopUI);
        }


        void InGameUIManager::Update()
        {
            for (auto* notify : m_notifyList)
            {
                switch (notify->m_notifyType)
                {
                    case enNotifyType_CrossHair:
                    {
                        const auto* crossHairNotify= static_cast<const CrossHairNotify*>(notify);

                        m_crosshairUI->SetIsHit(crossHairNotify->m_isHit);
                    }

                    case enNotifyType_RemainingBullets:
                    {
                        const auto* remainingNotify = static_cast<const RemainingBulletsNotify*>(notify);
                        
                        m_remainingBulletsUI->SetMaxAmmo(remainingNotify->m_maxNum);
                        m_remainingBulletsUI->SetAmmo(remainingNotify->m_remainingNum);

                        break;
                    }

                    case enNotifyType_Score:
                    {
                        const auto* scoreNotify = static_cast<const ScoreNotify*>(notify);

                        m_scoreUI->SetScore(scoreNotify->m_score);

                        break;
                    }

                    case enNotifyType_RemainingEnemies:
                    {
                        const auto* remainingEnemiesNotify = static_cast<const RemainingEnemiesNotify*>(notify);

                        m_remainingEnemyUI->SetEnemyCount(remainingEnemiesNotify->m_remainingEnemy);

                        break;
                    }

                    case enNotifyType_Enemies:
                    {
                        const auto* enemiesNotify = static_cast<const EnemiesNotify*>(notify);

                        m_miniMapUI->UpdateIconInformation(enemiesNotify->m_iconId, enemiesNotify->m_id, enemiesNotify->m_position);

                        break;
                    }

                    case enNotifyType_Countdown:
                    {
                        const auto* countdownNotify = static_cast<const CountdownNotify*>(notify);

                        m_countdownUI->SetSpecifiedSeconds(countdownNotify->m_specifiedSeconds);
                        m_countdownUI->SetCurrentSeconds(countdownNotify->m_currentSeconds);
                        m_countdownUI->SetDrawCount(countdownNotify->m_isDrawCount);

                        break;
                    }

                    case enNotifyType_WallHP:
                    {
                        const auto* wallHPNotify = static_cast<const WallHPNotify*>(notify);

                        m_wallHPUI->SetMaxDurability(wallHPNotify->m_maxWallHP);
                        m_wallHPUI->SetDurability(wallHPNotify->m_wallHP);

                        break;
                    }

                    case enNotifyType_Shop:
                    {
                        const auto* shopNotify = static_cast<const ShopNotify*>(notify);

                        m_shopUI->SetIndex(shopNotify->m_menuIndex);
                        m_shopUI->SetIsOpen(shopNotify->m_isOpen);

                        break;
                    }

                    default:
                    {
                        K2_ASSERT(false, "追加されてません");
                        break;
                    }
                }
                // 通知処理終わったので削除
                delete notify;
                notify = nullptr;
            }
            m_notifyList.clear();
        }
    }
}