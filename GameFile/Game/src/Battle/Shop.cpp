/**
 * Shop.cpp
 *
 * ショップクラス
 */
#include "stdafx.h"
#include "Shop.h"
#include "src/Core/BattleManager.h"
#include "src/Actor/Gun/AssaultRifle.h"
#include "src/Actor/Gun/HandGun.h"
#include "src/GameFlow/GameFlowManager.h"


namespace nsApp
{
    namespace nsBattle
    {
		Shop* Shop::m_instance = nullptr;

        Shop::Shop()
        {
            //todo for test
            m_menuIndex = 0;
            m_menuIndexMax = 1;
            m_menuIndexLineBreak = 1;
        }

        
        Shop::~Shop()
        {
        }

       
        void Shop::Update()
        {
            //メニュー画面の開閉
            if (nsFlow::GameFlowManager::GetInstance()->GetGameFlow() == enPreparation
                && g_pad[0]->IsTrigger(enButtonY)) {
                if (m_isOpenMenu) m_isOpenMenu = false;
                else {
                    m_isOpenMenu = true;
                    m_menuIndex = 0;
                }
            }
            else if (nsFlow::GameFlowManager::GetInstance()->GetGameFlow() != enPreparation) m_isOpenMenu = false;

            if (!m_isOpenMenu) return;
            OperateMenu();
            BuyProducts();
        }

        void Shop::OperateMenu()
        {
            //右に移動
            if (g_pad[0]->IsTrigger(enButtonRight)) {
                if (m_menuIndex % m_menuIndexLineBreak != 0 || m_menuIndex == 0) {
                    m_menuIndex++;
                }
            }

			//左に移動
            if (g_pad[0]->IsTrigger(enButtonLeft)) {
                if (m_menuIndex % m_menuIndexLineBreak + 1 != 0 && m_menuIndex != 0) {
                    m_menuIndex--;
                }
            }

            //上に移動
            //if (g_pad[0]->IsTrigger(enButtonUp)) {
            //    if (m_menuIndex - m_menuIndexLineBreak + 1 < 0) m_menuIndex = m_menuIndexMax - m_menuIndexLineBreak + m_menuIndex;
            //    else m_menuIndex -= m_menuIndexLineBreak + 1;
            //}

            ////下に移動
            //if (g_pad[0]->IsTrigger(enButtonDown)) {
            //    if (m_menuIndex + m_menuIndexLineBreak + 1 < m_menuIndexMax)m_menuIndex = m_menuIndexLineBreak + m_menuIndex;
            //    else m_menuIndex += m_menuIndexLineBreak + 1;
            //}
        }


        void Shop::BuyProducts()
        {
            if (!g_pad[0]->IsTrigger(enButtonA) || !m_isOpenMenu) return;

            //todo インデックスを渡してやるのいやっすね
            switch (m_menuIndex)
            {
                //サブウェポン購入
                case 0:
                {
                    BuyGuns(nsActor::nsGun::HandGun::ID());

                    break;
                }

                //メインウェポン購入
                case 1:
                {
                    BuyGuns(nsActor::nsGun::AssaultRifle::ID());

                    break;
                }

            

            default:
                break;
            }
        }


        void Shop::BuyGuns(const uint32_t gunID)
        {
            //インベントリにIDあげる
            nsBattle::BuyGunNotify* buyGunNotify = new nsBattle::BuyGunNotify();
            buyGunNotify->m_gunID = gunID;

            nsCore::BattleManager::GetInstance()->AddNotify(buyGunNotify);
            RequestChangeWeapon(gunID);
        }


        void Shop::RequestChangeWeapon(uint32_t weaponID)
        {
			nsCore::BattleManager::GetInstance()->RequestChangeWeapon(weaponID);
        }
    }
}