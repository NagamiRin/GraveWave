/**
 * ShopUI.cpp
 *
 * ショップUIの描画
 */
#include "stdafx.h"
#include "ShopUI.h"
#include "src/UI/UIBase.h"
#include "src/Core/BattleManager.h"
#include "src/Core/ParameterManager.h"
#include "src/GameFlow/GameFlowManager.h"


namespace nsApp
{
    namespace nsUI
    {
        ShopUI::ShopUI()
        {
            ParameterManager::Get().LoadParameter<MasterShopUIParameter>("Assets/Parameter/UI/ShopUIParameter.json", [](const nlohmann::json& j, MasterShopUIParameter& p)
                {
                    p.m_backWidth = j["BackWidth"].get<float>();
                    p.m_backHeight = j["BackHeight"].get<float>();
                    p.m_iconWidth = j["IconWidth"].get<float>();
                    p.m_iconHeight = j["IconHeight"].get<float>();
                    p.m_positionX = j["PositionX"].get<float>();
                    p.m_positionY = j["PositionY"].get<float>();
                    p.m_stringPositionX = j["StringPositionX"].get<float>();
                    p.m_stringPositionY = j["StringPositionY"].get<float>();
                    p.m_price = j["Price"].get<uint16_t>();
                    p.m_weaponName = j["WeaponName"].get<std::string>();
                });
        }

        
        ShopUI::~ShopUI()
        {
            ParameterManager::Get().UnloadParameter<MasterShopUIParameter>();
        }

       
        bool ShopUI::Start()
        {
            // ショップUI全体の大きなキャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;

            // ショップ全体の背景
            auto* wholeBack = m_uiCanvas->CreateUI<ImageUI>();
            wholeBack->Initialize("Assets/UI/Shop/IconBack.dds", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            wholeBack->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.6f));

            //サブウェポン背景
            auto* subWeaponBack = m_uiCanvas->CreateUI<ImageUI>();
            subWeaponBack->Initialize("Assets/UI/Shop/IconBack.DDS", 350.0f, 30.0f, Vector3(-600.0f, 280.0f, 0.0f), Vector3::One, Quaternion::Identity);
            subWeaponBack->SetMulColor(Vector4(0.4f, 0.7f, 0.6f, 0.6f));

            // サブウェポン表示
            auto* subWeapon = m_uiCanvas->CreateUI<ImageUI>();
            subWeapon->Initialize("Assets/UI/Shop/SubWeapon.DDS", 200.0f, 30.0f, Vector3(-600.0f, 280.0f, 0.0f), Vector3::One, Quaternion::Identity);
            subWeapon->SetMulColor(Vector4::White);

            //メインウェポン背景
            auto* mainWeaponBack = m_uiCanvas->CreateUI<ImageUI>();
            mainWeaponBack->Initialize("Assets/UI/Shop/IconBack.DDS", 350.0f, 30.0f, Vector3(-230.0f, 280.0f, 0.0f), Vector3::One, Quaternion::Identity);
            mainWeaponBack->SetMulColor(Vector4(0.4f, 0.7f, 0.6f, 0.6f));

            // メインウェポン表示
            auto* mainWeapon = m_uiCanvas->CreateUI<ImageUI>();
            mainWeapon->Initialize("Assets/UI/Shop/MainWeapon.DDS", 200.0f, 30.0f, Vector3(-230.0f, 280.0f, 0.0f), Vector3::One, Quaternion::Identity);
            mainWeapon->SetMulColor(Vector4::White);

            // 各商品の背景、アイコン、値段、名前を表示する
            const auto& paramList = ParameterManager::Get().GetParameters<MasterShopUIParameter>();
            for (int i = 0; i < paramList.size(); i++) {
                auto param = paramList.at(i);

                // キャンバス生成
                auto* canvas = m_uiCanvas->CreateUI<UICanvas>();
                canvas->m_transform.m_localPosition = Vector3(param->m_positionX, param->m_positionY, 0.0f);

                // 背景表示
                auto* back = canvas->CreateUI<ImageUI>();
                back->Initialize("Assets/UI/Shop/IconBack.dds", param->m_backWidth, param->m_backHeight, Vector3::Zero, Vector3::One, Quaternion::Identity);
                back->SetMulColor(Vector4(0.5f, 0.5f, 0.5f, 0.4f));
                m_uiBackList.push_back(back);

                // アイコン表示
                auto* icon = canvas->CreateUI<ImageUI>();
                std::string iconPath = "Assets/UI/ItemIcon/" + param->m_weaponName + ".dds";
                icon->Initialize(iconPath.c_str(), param->m_iconWidth, param->m_iconHeight, Vector3(0.0f, 20.0f, 0.0f), Vector3::One, Quaternion::Identity);

                // $マーク表示
                auto* priceMark = canvas->CreateUI<ImageUI>();
                priceMark->Initialize("Assets/UI/Shop/$.dds", 15.0f, 20.0f, Vector3(param->m_stringPositionX - 30.0f, param->m_stringPositionY, 0.0f), Vector3::One, Quaternion::Identity);

                // 値段表示
                auto* price = canvas->CreateUI<NumberUI>();
                price->Initialize("Assets/UI/Numbers/Classic", param->m_price, 13.0f, 17.0f, Vector3(param->m_stringPositionX, param->m_stringPositionY, 0.0f), Vector3::One, Quaternion::Identity);
                price->SetColor(Vector4::White);

                // アイテム名表示
                auto* name = canvas->CreateUI<ImageUI>();
                std::string itemPath = "Assets/UI/Shop/" + param->m_weaponName + ".dds";
                name->Initialize(itemPath.c_str(), 50.0f, 17.0f, Vector3(param->m_stringPositionX, param->m_stringPositionY - 25.0f, 0.0f), Vector3::One, Quaternion::Identity);
                name->SetMulColor(Vector4::White);
            }

            m_uiCanvas->Update();
        
            return true;
        }

        
        void ShopUI::Update()
        {
            m_uiCanvas->Update();
            
            //現在選択している画像の色を変える
            if (m_beforeIndex == m_index) return;
            m_uiBackList[m_index]->SetMulColor(Vector4(0.5f, 0.8f, 0.7f, 0.5f));//ちょっと深めの緑
            m_uiBackList[m_beforeIndex]->SetMulColor(Vector4(0.5f, 0.5f, 0.5f, 0.4f));
            m_beforeIndex = m_index;
        }

        
        void ShopUI::Render(RenderContext& rc)
        {
            if (!m_isOpen) return;

            if(m_isOpen) m_uiCanvas->Render(rc);
        }
    }
}