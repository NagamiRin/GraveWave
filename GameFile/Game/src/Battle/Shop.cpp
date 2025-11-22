/**
 * Shop.cpp
 *
 * ショップクラス
 */
#include "stdafx.h"
#include "Shop.h"
#include "src/Core/BattleManager.h"
#include "src/Actor/Gun/AssaultRifle.h"


namespace nsApp
{
    namespace nsBattle
    {
		Shop* Shop::m_instance = nullptr;

        Shop::Shop()
        {
            //todo for test
            m_menuIndex = 2;
            m_menuIndexLineBreak = 2;
        }

        
        Shop::~Shop()
        {
        }

       
        void Shop::Update()
        {
            //todo for test
            //Yボタンで武器変更をリクエスト
            if (g_pad[0]->IsTrigger(enButtonY)) {
                //インベントリにARのIDあげる
                nsBattle::BuyGunNotify* buyGunNotify = new nsBattle::BuyGunNotify();

                //アサルトライフルのIDをセット
                buyGunNotify->m_gunID = nsActor::nsGun::AssaultRifle::ID();

                nsCore::BattleManager::GetInstance()->AddNotify(buyGunNotify);
				RequestChangeWeapon(nsActor::nsGun::AssaultRifle::ID());
            }
        }

        void Shop::OperateMenu()
        {
            //右に移動
            if (g_pad[0]->IsTrigger(enButtonRight)) {
				if (m_menuIndex == m_menuIndexMax) m_menuIndex -= m_menuIndexLineBreak;
                else m_menuIndex++;
            }
			//左に移動
            if (g_pad[0]->IsTrigger(enButtonLeft)) {
                if (m_menuIndex == 0 || m_menuIndex-- == m_menuIndexLineBreak)m_menuIndex += m_menuIndexLineBreak;
                else m_menuIndex--;
            }

            //範囲外チェック
			if (m_menuIndex < 0) m_menuIndex = 0;
        }


        void Shop::RequestChangeWeapon(uint32_t weaponID)
        {
			nsCore::BattleManager::GetInstance()->RequestChangeWeapon(weaponID);
        }
    }
}