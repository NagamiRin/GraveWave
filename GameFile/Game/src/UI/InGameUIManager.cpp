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
#include "src/UI/RemainingEnemyUI.h"
#include "src/UI/WallHPUI.h"


namespace nsApp
{
    namespace nsUI
    {
        InGameUIManager* InGameUIManager::m_instance = nullptr;


        InGameUIManager::InGameUIManager()
        {
            //クロスヘアを生成
            m_crosshair = NewGO<Crosshair>(enGameObjectPriority_UI, "Crosshair");
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
        }


        InGameUIManager::~InGameUIManager()
        {
            DeleteGO(m_crosshair);
            DeleteGO(m_countdownUI);
            DeleteGO(m_remainingBulletsUI);
            DeleteGO(m_scoreUI);
            DeleteGO(m_remainingEnemyUI);
            DeleteGO(m_wallHPUI);
        }


        void InGameUIManager::Update()
        {
            for (auto* notify : m_notifyList)
            {
                switch (notify->m_notifyType)
                {
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