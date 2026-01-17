/**
 * Shop.cpp
 *
 * ショップクラス
 */
#include "stdafx.h"
#include "Shop.h"
#include "src/Core/BattleManager.h"
#include "src/Actor/Gun/MainWeapon.h"
#include "src/Actor/Gun/SubWeapon.h"
#include "src/GameFlow/GameFlowManager.h"
#include "src/Core/ParameterManager.h"


namespace nsApp
{
    namespace nsBattle
    {
		Shop* Shop::m_instance = nullptr;

        Shop::Shop()
        {
            //商品の値段を設定
            ParameterManager::Get().LoadParameter<MasterShopParameter>("Assets/Parameter/ShopParameter.json", [](const nlohmann::json& j, MasterShopParameter& p)
                {
                    p.m_GZ75 = j["GZ75"].get<uint8_t>();
                    p.m_R8 = j["R8"].get<uint8_t>();
                    p.m_M1911 = j["M1911"].get<uint8_t>();
                    p.m_TEC9 = j["TEC9"].get<uint8_t>();
                    p.m_ACR = j["ACR"].get<uint8_t>();
                    p.m_AK47 = j["AK47"].get<uint8_t>();
                    p.m_G36 = j["G36"].get<uint8_t>();
                    p.m_HAMR = j["HAMR"].get<uint8_t>();
                    p.m_L86A2 = j["L86A2"].get<uint8_t>();
                    p.m_M4A1 = j["M4A1"].get<uint8_t>();
                    p.m_SCAR = j["SCAR"].get<uint8_t>();
                });

            auto* param = ParameterManager::Get().GetParameter< MasterShopParameter>();

            m_priceVar.emplace(enProductType_GZ75, param->m_GZ75);
            m_priceVar.emplace(enProductType_R8, param->m_R8);
            m_priceVar.emplace(enProductType_M1911, param->m_M1911);
            m_priceVar.emplace(enProductType_TEC9, param->m_TEC9);

            m_priceVar.emplace(enProductType_ACR, param->m_ACR);
            m_priceVar.emplace(enProductType_AK47, param->m_AK47);
            m_priceVar.emplace(enProductType_HAMR, param->m_G36);
            m_priceVar.emplace(enProductType_G36, param->m_HAMR);
            m_priceVar.emplace(enProductType_L86A2, param->m_L86A2);
            m_priceVar.emplace(enProductType_M4A1, param->m_M4A1);
            m_priceVar.emplace(enProductType_SCAR, param->m_SCAR);


            //インデックスごとの商品を設定
            {
                
            }


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
                    BuyGuns(nsActor::nsGun::SubWeapon::ID());

                    break;
                }

                //メインウェポン購入
                case 1:
                {
                    BuyGuns(nsActor::nsGun::MainWeapon::ID());

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